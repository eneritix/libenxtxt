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

#ifndef ENXTXT_FSTR_H
#define ENXTXT_FSTR_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/** \defgroup fstr Format strings
 *  @{
 */

typedef bool (enxtxt_fstr_output_function_t)(void *context, const char *ptr, size_t length);


struct enxtxt_fstr_arg
{
    void (*fn_fmt)(
        const struct enxtxt_fstr_arg *arg,
        enxtxt_fstr_output_function_t output_fn,
        void *output_fn_context
        );
    union {
        float _flt;
        double _dbl;
        int _int;
        unsigned int _uint;
        const char *_str;
        void * _user;
    };
};

struct enxtxt_fstr_h8_array_metadata
{
    const uint8_t *ptr;
    size_t length;
};

struct enxtxt_fstr_h16_array_metadata
{
    const uint16_t *ptr;
    size_t length;
};

struct enxtxt_fstr_h32_array_metadata
{
    const uint32_t *ptr;
    size_t length;
};

/* Internal format functions */
void enxtxt_fstr_fmt_int(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);
void enxtxt_fstr_fmt_uint(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);
void enxtxt_fstr_fmt_h8(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);
void enxtxt_fstr_fmt_h16(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);
void enxtxt_fstr_fmt_h32(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);
void enxtxt_fstr_fmt_str(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);
void enxtxt_fstr_fmt_h8_array(const struct enxtxt_fstr_arg *, enxtxt_fstr_output_function_t, void *);

/**
 * Formats a character array
 *
 * \param _val The value to format
 */
#define f_str(_val) \
    { .fn_fmt = enxtxt_fstr_fmt_str, ._str  = _val }

/**
 * Formats a signed integer as decimal
 *
 * \param _val The value to format
 */
#define f_int(_val) \
    { .fn_fmt = enxtxt_fstr_fmt_int, ._int  = _val }

/**
 * Formats an unsigned integer as decimal
 *
 * \param _val The value to format
 */
#define f_uint(_val) \
    { .fn_fmt = enxtxt_fstr_fmt_uint, ._uint = _val }

/**
 * Formats an 8 bit unsigned integer as hex
 *
 * \param _val The value to format
 */
#define f_h8(_val) \
    { .fn_fmt = enxtxt_fstr_fmt_h8, ._uint = _val }

/**
 * Formats a 16 bit unsigned integer as hex
 *
 * \param _val The value to format
 */
#define f_h16(_val) \
    { .fn_fmt = enxtxt_fstr_fmt_h16, ._uint = _val }

/**
 * Formats a 32 bit unsigned integer as hex
 *
 * \param _val The value to format
 */
#define f_h32(_val) \
    { .fn_fmt = enxtxt_fstr_fmt_h32, ._uint = _val }

/**
 * Formats an 8 bit integer array as hex
 *
 * \param _ptr A pointer to the array
 * \param _length The length of the array
 */
#define f_h8_array(_ptr, _length) \
    { .fn_fmt = enxtxt_fstr_fmt_h8_array, .value._user = (struct enxtxt_fstr_h8_array_metadata []) {{ .ptr = _ptr, .length = _length}} }





bool _enxtxt_fstr_cb(
    enxtxt_fstr_output_function_t output_fn,
    void *output_fn_context,
    const char* format,
    const struct enxtxt_fstr_arg *args);

bool _enxtxt_fstr_sz(
    char *ptr,
    size_t length,
    const char* format,
    const struct enxtxt_fstr_arg *args);


#define enxtxt_fstr_cb(_output_fn, _output_fn_context, _format, ...)                    \
({                                                                                      \
    bool result;                                                                        \
    const struct enxtxt_fstr_arg *__args = (const struct enxtxt_fstr_arg []) {          \
    __VA_ARGS__                                                                         \
    };                                                                                  \
    result = _enxtxt_fstr_cb(_output_fn, _output_fn_context, _format, __args);          \
    result;                                                                             \
})

#define enxtxt_fstr_sz(_ptr, _length, _format, ...)                                     \
({                                                                                      \
    bool result;                                                                        \
    const struct enxtxt_fstr_arg *__args = (const struct enxtxt_fstr_arg []) {          \
    __VA_ARGS__                                                                         \
    };                                                                                  \
    result = _enxtxt_fstr_sz(_ptr, _length, _format, __args);                           \
    result;                                                                             \
})


__END_DECLS

#endif
