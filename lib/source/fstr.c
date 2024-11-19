/*
    Copyright (c) 2022 Eneritix (Pty) Ltd

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

#include <enx/txt/fstr.h>
#include <enx/txt/format.h>
#include <string.h>
#include <stdio.h>


struct enxtxt_str_format_context
{
    char *ptr;
    size_t length;
};

static bool enxtxt_str_format_output_function(void *context, const char *ptr, size_t length);



bool _enxtxt_fstr_cb(
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context,
    const char* format,
    const struct enxtxt_fstr_arg *args)
{
    do {
        const char *ptr = format;
        while ((*ptr != '{') && (*ptr != '\n') && (*ptr != 0)) {
            ptr++;
        }

        output_fn(output_fn_context, format, ptr - format);

        if (*ptr == '{') {
            while ((*ptr != '}') && (*ptr != 0)) {
                ptr++;
            }

            if (*ptr == '}') {
                if (args->fn_fmt) {
                    args->fn_fmt(args, output_fn, output_fn_context);
                }
                args++;
                ptr++;
            }
        }

        if (*ptr == '\n') {
            output_fn(output_fn_context, ptr, 1);
            ptr++;
        }

        format = ptr;

    } while (*format != 0);

    return true;
}


bool _enxtxt_fstr_sz(
    char *ptr,
    size_t length,
    const char* format,
    const struct enxtxt_fstr_arg *args)
{
    struct enxtxt_str_format_context context = {
        .ptr = ptr,
        .length = length
    };

    bool result = _enxtxt_fstr_cb(
        enxtxt_str_format_output_function,
        &context,
        format,
        args
    );

    if (result) {
        *context.ptr = 0;
    }

    return result;
}

static bool enxtxt_str_format_output_function(
    void *context,
    const char *ptr,
    size_t length)
{
    struct enxtxt_str_format_context *obj = (struct enxtxt_str_format_context *)context;

    if (length >= obj->length) {
        return false;
    }

    memcpy(obj->ptr, ptr, length);
    obj->ptr += length;
    obj->length -= length;

    return true;
}


void enxtxt_fstr_fmt_int(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_s32_dec(arg->_int);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_uint(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u32_dec(arg->_uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_size(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context) {

#if (SIZE_MAX == 0xFFFF)
    struct enxtxt_fmt_result result = enxtxt_fmt_u16_dec((uint16_t)arg->_size);
#elif (SIZE_MAX == 0xFFFFFFFF)
    struct enxtxt_fmt_result result = enxtxt_fmt_u32_dec((uint32_t)arg->_size);
#else
    struct enxtxt_fmt_result result = enxtxt_fmt_u64_dec((uint64_t)arg->_size);
#endif

    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_s64(const struct enxtxt_fstr_arg *arg, enxtxt_fstr_output_function_t output_fn, void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_s64_dec(arg->_u64);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_u64(const struct enxtxt_fstr_arg *arg, enxtxt_fstr_output_function_t output_fn, void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u64_dec(arg->_s64);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_flt(
    const struct enxtxt_fstr_arg * arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_flt(arg->_flt);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_dbl(
    const struct enxtxt_fstr_arg * arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_dbl(arg->_dbl);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_flt_n(
    const struct enxtxt_fstr_arg * arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_flt_n(arg->_flt, arg->_param);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_dbl_n(
    const struct enxtxt_fstr_arg * arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_dbl_n(arg->_dbl, arg->_param);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_h8(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u8_hex(arg->_uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_h16(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u16_hex(arg->_uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_h32(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u32_hex(arg->_uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_str(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    output_fn(output_fn_context, arg->_str, strlen(arg->_str));
}

void enxtxt_fstr_fmt_h8_array(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    const struct enxtxt_fstr_h8_array_metadata *data = (const struct enxtxt_fstr_h8_array_metadata *)arg->_user;
    char format_buffer[32];

    const unsigned char *ptr = data->ptr;
    size_t length = data->length;

    while (length) {
        struct enxtxt_fmt_array_result result = enxtxt_fmt_u8_hex_array(ptr, length, " ", format_buffer, sizeof(format_buffer));
        output_fn(output_fn_context, format_buffer, result.bytes_written);
        ptr += result.entries_processed;
        length -= result.entries_processed;
    }
}
