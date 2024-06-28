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

/** @defgroup pl_ex Pointer and length extended functions
 *  @{
 */

/**
 * @brief Decimal to signed 32 bit
 */
int32_t  enxtxt_dec_to_s32_pl_ex(const char *ptr, size_t length, const char **pos, bool *result);

/**
 * @brief Decimal to unsigned 32 bit
 */
uint32_t enxtxt_dec_to_u32_pl_ex(const char *ptr, size_t length, const char **pos, bool *result);

/**
 * @brief Hexadecimal to unsigned 32 bit
 * @note This function will stop to consume digits after 8 digits have been processed, even
 *       if there is more digits available
 */
uint32_t enxtxt_hex_to_u32_pl_ex(const char *ptr, size_t length, const char **pos, bool *result);

/**
 * @brief Hexadecimal to unsigned 16 bit
 * @note This function will stop to consume digits after 4 digits have been processed, even
 *       if there is more digits available
 */
uint16_t enxtxt_hex_to_u16_pl_ex(const char *ptr, size_t length, const char **pos, bool *result);

/**
 * @brief Hexadecimal to unsigned 8 bit
 * @note This function will stop to consume digits after 2 digits have been processed, even
 *       if there is more digits available
 */
uint8_t enxtxt_hex_to_u8_pl_ex(const char *ptr, size_t length, const char **pos, bool *result);

/** @} */


/** @defgroup nt_ex Null terminated string extended functions
 *  @{
 */

/**
 * @brief Decimal to signed 32 bit
 */
int32_t  enxtxt_dec_to_s32_nt_ex(const char *str, const char **pos, bool *result);

/**
 * @brief Decimal to unsigned 32 bit
 */
uint32_t enxtxt_dec_to_u32_nt_ex(const char *str, const char **pos, bool *result);

/**
 * @brief Hexadecimal to unsigned 32 bit
 */
uint32_t enxtxt_hex_to_u32_nt_ex(const char *str, const char **pos, bool *result);

/** @} */


/** @defgroup pl Pointer and length functions
 *  @{
 */

/**
 * @brief Decimal to signed 32 bit
 */
int32_t  enxtxt_dec_to_s32_pl(const char *ptr, size_t length);

/**
 * @brief Decimal to unsigned 32 bit
 */
uint32_t enxtxt_dec_to_u32_pl(const char *ptr, size_t length);

/**
 * @brief Hexadecimal to unsigned 32 bit
 */
uint32_t enxtxt_hex_to_u32_pl(const char *ptr, size_t length);

/** @} */


/** @defgroup nt Null terminated string functions
 *  @{
 */

/**
 * @brief Decimal to signed 32 bit
 */
int32_t  enxtxt_dec_to_s32_nt(const char *str);

/**
 * @brief Decimal to unsigned 32 bit
 */
uint32_t enxtxt_dec_to_u32_nt(const char *str);

/**
 * @brief Hexadecimal to unsigned 32 bit
 */
uint32_t enxtxt_hex_to_u32_nt(const char *str);

/** @} */


/** @defgroup array_pl Pointer and length array functions
 *  @{
 */

size_t enxtxt_hex_to_u8_array_pl(
    const char *ptr,
    size_t length,
    uint8_t *result,
    size_t result_length);

/** @} */

__END_DECLS

#endif
