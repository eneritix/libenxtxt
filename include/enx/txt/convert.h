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

#ifndef ENXTXT_CONVERT_H
#define ENXTXT_CONVERT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * @brief Conversion result
 * 
 * The buffer has enough space to hold up to a 64 bit
 * unsigned integer conversion.
 * 
 */
struct enxtxt_conv_result 
{
    char str[24];
    size_t length;
};

/**
 * @brief Converts a 32 bit unsigned integer to a decimal string
 */
struct enxtxt_conv_result enxtxt_conv_u32_to_dec(uint32_t value);

/**
 * @brief Converts a 32 bit signed integer to a decimal string
 */
struct enxtxt_conv_result enxtxt_conv_s32_to_dec(int32_t value);

/**
 * @brief Converts a 16 bit unsigned integer to a decimal string
 */
struct enxtxt_conv_result enxtxt_conv_u16_to_dec(uint16_t value);

/**
 * @brief Converts a 16 bit signed integer to a decimal string
 */
struct enxtxt_conv_result enxtxt_conv_s16_to_dec(int16_t value);

/**
 * @brief Converts an 8 bit unsigned integer to a decimal string
 */
struct enxtxt_conv_result enxtxt_conv_u8_to_dec(uint8_t value);

/**
 * @brief Converts an 8 bit signed integer to a decimal string
 */
struct enxtxt_conv_result enxtxt_conv_s8_to_dec(int8_t value);

/**
 * @brief Converts a 32 bit unsigned integer to a hexadecimal string
 */
struct enxtxt_conv_result enxtxt_conv_u32_to_hex(uint32_t value);

/**
 * @brief Converts a 16 bit unsigned integer to a hexadecimal string
 */
struct enxtxt_conv_result enxtxt_conv_u16_to_hex(uint16_t value);

/**
 * @brief Converts an 8 bit unsigned integer to a hexadecimal string
 */
struct enxtxt_conv_result enxtxt_conv_u8_to_hex(uint8_t value);


__END_DECLS

#endif
