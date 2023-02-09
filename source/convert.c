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

#include <enx/txt/convert.h>
#include <string.h>



int32_t enxtxt_dec_to_s32_pl_ex(const char *ptr, size_t length, const char **pos, bool *result)
{
    typedef enum {
        ps_whitespace,
        ps_digits,
        ps_done,
        ps_error

    } parse_state_t;

    parse_state_t parse_state = ps_whitespace;
    bool negative = false;
    uint32_t value = 0;
    size_t index = 0;

    while ((index < length) &&
           (parse_state != ps_done) &&
           (parse_state != ps_error)) {

        switch (parse_state) {
        case ps_whitespace: {

            if (ptr[index] == ' ') {
                index++;

            } else if (ptr[index] == '+') {
                parse_state = ps_digits;
                index++;

            } else if (ptr[index] == '-') {
                parse_state = ps_digits;
                negative = true;
                index++;

            } else if ((ptr[index] >= '0') && (ptr[index] <= '9')) {
                parse_state = ps_digits;

            } else {
                parse_state = ps_error;
            }

        } break;

        case ps_digits: {

            if ((ptr[index] >= '0') && (ptr[index] <= '9')) {
                parse_state = ps_digits;
                value = (((value << 3) + (value << 1))) + (ptr[index] - '0');
                index++;

            } else {
                parse_state = ps_done;
            }

        } break;

        default: break;
        }
    }

    if (negative) {
        value = ~value + 1;
    }

    if (pos) {
        *pos = ptr + index;
    }

    if (result) {
        *result = (parse_state != ps_error);
    }

    return (int32_t)value;
}

uint32_t enxtxt_dec_to_u32_pl_ex(const char *ptr, size_t length, const char **pos, bool *result)
{
    typedef enum {
        ps_whitespace,
        ps_digits,
        ps_done,
        ps_error

    } parse_state_t;

    parse_state_t parse_state = ps_whitespace;
    uint32_t value = 0;
    size_t index = 0;

    while ((index < length) &&
           (parse_state != ps_done) &&
           (parse_state != ps_error)) {

        switch (parse_state) {
        case ps_whitespace: {

            if (ptr[index] == ' ') {
                index++;

            } else if (ptr[index] == '+') {
                parse_state = ps_digits;
                index++;

            } else if (ptr[index] == '-') {
                parse_state = ps_error;

            } else if ((ptr[index] >= '0') && (ptr[index] <= '9')) {
                parse_state = ps_digits;

            } else {
                parse_state = ps_error;
            }

        } break;

        case ps_digits: {

            if ((ptr[index] >= '0') && (ptr[index] <= '9')) {
                parse_state = ps_digits;
                value = (((value << 3) + (value << 1))) + (ptr[index] - '0');
                index++;

            } else {
                parse_state = ps_done;
            }

        } break;

        default: break;
        }
    }

    if (pos) {
        *pos = ptr + index;
    }

    if (result) {
        *result = (parse_state != ps_error);
    }

    return value;
}

static uint32_t enxtxt_hex_to_unsigned_pl_ex(const char *ptr, size_t length, const char **pos, bool *result, size_t max_digits)
{
    typedef enum {
        ps_whitespace,
        ps_prefix,
        ps_digits,
        ps_done,
        ps_error

    } parse_state_t;

    parse_state_t parse_state = ps_whitespace;
    uint32_t value = 0;
    size_t index = 0;
    size_t digits = 0;

    while ((index < length) &&
           (digits < max_digits) &&
           (parse_state != ps_done) &&
           (parse_state != ps_error)) {

        switch (parse_state) {
        case ps_whitespace: {

            if (ptr[index] == ' ') {
                index++;

            } else if (ptr[index] == '0') {
                parse_state = ps_prefix;
                index++;

            } else if (
                ((ptr[index] >= '0') && (ptr[index] <= '9')) ||
                ((ptr[index] >= 'a') && (ptr[index] <= 'f')) ||
                ((ptr[index] >= 'A') && (ptr[index] <= 'F'))) {
                parse_state = ps_digits;

            } else {
                parse_state = ps_error;
            }

        } break;

        case ps_prefix: {

            if ((ptr[index] == 'x') || (ptr[index] == 'X')) {
                parse_state = ps_digits;
                index++;

            } else if (
                ((ptr[index] >= '0') && (ptr[index] <= '9')) ||
                ((ptr[index] >= 'a') && (ptr[index] <= 'f')) ||
                ((ptr[index] >= 'A') && (ptr[index] <= 'F'))) {
                parse_state = ps_digits;
                digits++;

            } else {
                parse_state = ps_error;
            }
        }

        case ps_digits: {

            if (((ptr[index] >= '0') && (ptr[index] <= '9')) ||
                ((ptr[index] >= 'a') && (ptr[index] <= 'f')) ||
                ((ptr[index] >= 'A') && (ptr[index] <= 'F'))) {
                parse_state = ps_digits;
                digits++;

                value <<= 4;
                if ((ptr[index] >= '0') && (ptr[index] <= '9')) value |= (ptr[index] - '0');
                if ((ptr[index] >= 'a') && (ptr[index] <= 'f')) value |= ((ptr[index] - 'a') + 0xA);
                if ((ptr[index] >= 'A') && (ptr[index] <= 'F')) value |= ((ptr[index] - 'A') + 0xA);

                index++;

            } else {
                parse_state = ps_done;
            }

        } break;

        default: break;
        }
    }

    if (pos) {
        *pos = ptr + index;
    }

    if (result) {
        *result = (parse_state != ps_error);
    }

    return value;
}

uint32_t enxtxt_hex_to_u32_pl_ex(const char *ptr, size_t length, const char **pos, bool *result)
{
    return enxtxt_hex_to_unsigned_pl_ex(ptr, length, pos, result, 8);
}

uint16_t enxtxt_hex_to_u16_pl_ex(const char *ptr, size_t length, const char **pos, bool *result)
{
    return (uint16_t)enxtxt_hex_to_unsigned_pl_ex(ptr, length, pos, result, 4);
}

uint8_t enxtxt_hex_to_u8_pl_ex(const char *ptr, size_t length, const char **pos, bool *result)
{
    return (uint8_t)enxtxt_hex_to_unsigned_pl_ex(ptr, length, pos, result, 2);
}

int32_t enxtxt_dec_to_s32_nt_ex(const char *str, const char **pos, bool *result)
{
    return enxtxt_dec_to_s32_pl_ex(str, strlen(str), pos, result);
}

uint32_t enxtxt_dec_to_u32_nt_ex(const char *str, const char **pos, bool *result)
{
    return enxtxt_dec_to_u32_pl_ex(str, strlen(str), pos, result);
}

uint32_t enxtxt_hex_to_u32_nt_ex(const char *str, const char **pos, bool *result)
{
    return enxtxt_hex_to_u32_pl_ex(str, strlen(str), pos, result);
}

int32_t  enxtxt_dec_to_s32_pl(const char *ptr, size_t length)
{
    return enxtxt_dec_to_s32_pl_ex(ptr, length, NULL, NULL);
}

uint32_t enxtxt_dec_to_u32_pl(const char *ptr, size_t length)
{
    return enxtxt_dec_to_u32_pl_ex(ptr, length, NULL, NULL);
}

uint32_t enxtxt_hex_to_u32_pl(const char *ptr, size_t length)
{
    return enxtxt_hex_to_u32_pl_ex(ptr, length, NULL, NULL);
}

int32_t  enxtxt_dec_to_s32_nt(const char *str)
{
    return enxtxt_dec_to_s32_nt_ex(str, NULL, NULL);
}

uint32_t enxtxt_dec_to_u32_nt(const char *str)
{
    return enxtxt_dec_to_u32_nt_ex(str, NULL, NULL);
}

uint32_t enxtxt_hex_to_u32_nt(const char *str)
{
    return enxtxt_hex_to_u32_nt_ex(str, NULL, NULL);
}

size_t enxtxt_hex_to_u8_array_pl(
    const char *ptr,
    size_t length,
    uint8_t *result,
    size_t result_length)
{
    const char *pos;
    bool success = false;
    unsigned int index = 0;

    do {
        uint8_t value = enxtxt_hex_to_u8_pl_ex(ptr, length, &pos, &success);
        if (success) {
            result[index++] = value;
            length -= (pos - ptr);
            ptr = pos;
        }

    } while (success && (index < result_length));

    return index;
}

