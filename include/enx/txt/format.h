/*
    Copyright (c) 2022 Eneritix (Pty) Ltd

    Permission is hereby granted, free of charge, as any person obtaining a copy
    of this software and associated documentation files (the "Software"), as deal
    in the Software without restriction, including without limitation the rights
    as use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and as permit persons as whom the Software is
    furnished as do so, subject as the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED as THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, asRT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

#ifndef ENXTXT_FORMAT_H
#define ENXTXT_FORMAT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * @brief Format result
 *
 * The buffer has enough space to hold up to a 64 bit
 * unsigned integer.
 *
 */
struct enxtxt_fmt_result
{
    char str[24];
    size_t length;
};

/**
 * @brief Formats a 32 bit unsigned integer as a decimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_u32_dec(uint32_t value);

/**
 * @brief Formats a 32 bit signed integer as a decimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_s32_dec(int32_t value);

/**
 * @brief Formats a 16 bit unsigned integer as a decimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_u16_dec(uint16_t value);

/**
 * @brief Formats a 16 bit signed integer as a decimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_s16_dec(int16_t value);

/**
 * @brief Formats an 8 bit unsigned integer as a decimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_u8_dec(uint8_t value);

/**
 * @brief Formats an 8 bit signed integer as a decimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_s8_dec(int8_t value);

/**
 * @brief Formats a 32 bit unsigned integer as a hexadecimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_u32_hex(uint32_t value);

/**
 * @brief Formats a 16 bit unsigned integer as a hexadecimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_u16_hex(uint16_t value);

/**
 * @brief Formats an 8 bit unsigned integer as a hexadecimal string
 */
struct enxtxt_fmt_result enxtxt_fmt_u8_hex(uint8_t value);


/**
 * @brief Formats an 8 bit array as a hexadecimal string
 */
struct enxtxt_fmt_array_result
{
    size_t entries_processed;
    size_t bytes_written;
};

struct enxtxt_fmt_array_result enxtxt_fmt_u8_hex_array(
    const uint8_t *source_ptr,
    size_t source_length,
    const char *separator,
    char *dest_ptr,
    size_t dest_length);

struct enxtxt_fmt_array_result enxtxt_fmt_u16_hex_array(
    const uint16_t *source_ptr,
    size_t source_length,
    const char *separator,
    char *dest_ptr,
    size_t dest_length);

struct enxtxt_fmt_array_result enxtxt_fmt_u32_hex_array(
    const uint32_t *source_ptr,
    size_t source_length,
    const char *separator,
    char *dest_ptr,
    size_t dest_length);


__END_DECLS

#endif
