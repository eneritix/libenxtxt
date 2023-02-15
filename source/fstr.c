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

#include "fstr.h"
#include <enx/txt/format.h>
#include <string.h>


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
        while ((*ptr != '{') && (*ptr != 0)) {
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

        format = ptr;

    } while (*format != 0);
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
    struct enxtxt_fmt_result result = enxtxt_fmt_s32_dec(arg->value._int);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_uint(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u32_dec(arg->value._uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_h8(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u8_hex(arg->value._uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_h16(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u16_hex(arg->value._uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_h32(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    struct enxtxt_fmt_result result = enxtxt_fmt_u32_hex(arg->value._uint);
    output_fn(output_fn_context, result.str, result.length);
}

void enxtxt_fstr_fmt_str(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    output_fn(output_fn_context, arg->value._str, strlen(arg->value._str));
}

void enxtxt_fstr_fmt_h8_array(
    const struct enxtxt_fstr_arg *arg,
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context)
{
    const struct enxtxt_fstr_h8_array_metadata *data = (const struct enxtxt_fstr_h8_array_metadata *)arg->value._user;
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