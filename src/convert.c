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

#include "convert.h"


static size_t enxtxt_conv_u32_to_dec_in_place(uint32_t value, char *result);
static size_t enxtxt_conv_s32_to_dec_in_place(int32_t value, char *result);

static size_t enxtxt_conv_u16_to_dec_in_place(uint16_t value, char *result);
static size_t enxtxt_conv_s16_to_dec_in_place(int16_t value, char *result);

static size_t enxtxt_conv_u8_to_dec_in_place(uint8_t value, char *result);
static size_t enxtxt_conv_s8_to_dec_in_place(int8_t value, char *result);

static size_t enxtxt_conv_u32_to_hex_in_place(uint32_t value, char *result);
static size_t enxtxt_conv_u16_to_hex_in_place(uint16_t value, char *result);
static size_t enxtxt_conv_u8_to_hex_in_place(uint8_t value, char *result);


static const char enxtxt_hex_digits[] = 
{
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
};


static size_t enxtxt_conv_u32_to_dec_in_place(uint32_t value, char *result)
{
    /* https://en.wikipedia.org/wiki/Double_dabble */

    char *ptr = result;
    uint32_t reg0, reg1;
    uint32_t i = 0;
    uint8_t digit;
    bool output;

    reg0 = 0;
    reg1 = 0;


    for (i=0; i < 32; ++i) {

        /* uint32_t max is 4294967296 (10 digits). We need to process
         * all the nibbles of reg0 and only the first two nibbles of reg1.
         * The operations for the rest of the nibbles are kept for completeness
         * but commented out for performance.
         */
        /* if ((reg1 & 0xF0000000) >= 0x50000000) reg1 += 0x30000000; */
        /* if ((reg1 & 0x0F000000) >= 0x05000000) reg1 += 0x03000000; */
        /* if ((reg1 & 0x00F00000) >= 0x00500000) reg1 += 0x00300000; */
        /* if ((reg1 & 0x000F0000) >= 0x00050000) reg1 += 0x00030000; */
        /* if ((reg1 & 0x0000F000) >= 0x00005000) reg1 += 0x00003000; */
        /* if ((reg1 & 0x00000F00) >= 0x00000500) reg1 += 0x00000300; */
        if ((reg1 & 0x000000F0) >= 0x00000050) reg1 += 0x00000030;
        if ((reg1 & 0x0000000F) >= 0x00000005) reg1 += 0x00000003;

        if ((reg0 & 0xF0000000) >= 0x50000000) reg0 += 0x30000000;
        if ((reg0 & 0x0F000000) >= 0x05000000) reg0 += 0x03000000;
        if ((reg0 & 0x00F00000) >= 0x00500000) reg0 += 0x00300000;
        if ((reg0 & 0x000F0000) >= 0x00050000) reg0 += 0x00030000;
        if ((reg0 & 0x0000F000) >= 0x00005000) reg0 += 0x00003000;
        if ((reg0 & 0x00000F00) >= 0x00000500) reg0 += 0x00000300;
        if ((reg0 & 0x000000F0) >= 0x00000050) reg0 += 0x00000030;
        if ((reg0 & 0x0000000F) >= 0x00000005) reg0 += 0x00000003;

        /* Shift */
        reg1 <<= 1;
        reg1 |= (reg0 >> 31);

        reg0 <<= 1;
        reg0 |= (value >> 31);

        value <<= 1;
    }

    // Collect
    output = false;

    /* digit = ((reg1 & 0xF0000000) >> 28); output |= (digit > 0); if (output) *result++ = ('0' + digit); */
    /* digit = ((reg1 & 0x0F000000) >> 24); output |= (digit > 0); if (output) *result++ = ('0' + digit); */
    /* digit = ((reg1 & 0x00F00000) >> 20); output |= (digit > 0); if (output) *result++ = ('0' + digit); */
    /* digit = ((reg1 & 0x000F0000) >> 16); output |= (digit > 0); if (output) *result++ = ('0' + digit); */
    /* digit = ((reg1 & 0x0000F000) >> 12); output |= (digit > 0); if (output) *result++ = ('0' + digit); */
    /* digit = ((reg1 & 0x00000F00) >> 8 ); output |= (digit > 0); if (output) *result++ = ('0' + digit); */
    digit = ((reg1 & 0x000000F0) >> 4 ); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg1 & 0x0000000F) >> 0 ); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);

    digit = ((reg0 & 0xF0000000) >> 28); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x0F000000) >> 24); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x00F00000) >> 20); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x000F0000) >> 16); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x0000F000) >> 12); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x00000F00) >> 8 ); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x000000F0) >> 4 ); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg0 & 0x0000000F) >> 0 );                                    *ptr++ = ('0' + digit);

    *ptr++ = 0;

    return (ptr - result - 1);
}

static size_t enxtxt_conv_s32_to_dec_in_place(int32_t value, char *result)
{
    char *ptr = result;
    const int32_t mask = (value >> 31);
    const uint32_t absolute_value = ((value + mask) ^ mask);

    if (mask) {
        *ptr++ = '-';
    }

    return ((ptr - result) + enxtxt_conv_u32_to_dec_in_place(absolute_value, ptr));
}

static size_t enxtxt_conv_u16_to_dec_in_place(uint16_t value, char *result)
{
    /* https://en.wikipedia.org/wiki/Double_dabble */

    char *ptr = result;
    uint32_t reg;
    uint32_t i = 0;
    uint8_t digit;
    bool output;

    reg = 0;


    for (i=0; i < 16; ++i) {

        /* uint16_t max is 65536 (5 digits). */
        if ((reg & 0x000F0000) >= 0x00050000) reg += 0x00030000;
        if ((reg & 0x0000F000) >= 0x00005000) reg += 0x00003000;
        if ((reg & 0x00000F00) >= 0x00000500) reg += 0x00000300;
        if ((reg & 0x000000F0) >= 0x00000050) reg += 0x00000030;
        if ((reg & 0x0000000F) >= 0x00000005) reg += 0x00000003;

        /* Shift */
        reg <<= 1;
        reg |= (value >> 15);

        value <<= 1;
    }

    // Collect
    output = false;

    digit = ((reg & 0x000F0000) >> 16); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg & 0x0000F000) >> 12); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg & 0x00000F00) >> 8 ); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg & 0x000000F0) >> 4 ); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg & 0x0000000F) >> 0 );                                    *ptr++ = ('0' + digit);

    *ptr++ = 0;

    return (ptr - result - 1);
}

static size_t enxtxt_conv_s16_to_dec_in_place(int16_t value, char *result)
{
    char *ptr = result;
    const int16_t mask = (value >> 31);
    const uint16_t absolute_value = ((value + mask) ^ mask);

    if (mask) {
        *ptr++ = '-';
    }

    return ((ptr - result) + enxtxt_conv_u16_to_dec_in_place(absolute_value, ptr));
}

static size_t enxtxt_conv_u8_to_dec_in_place(uint8_t value, char *result)
{
    /* https://en.wikipedia.org/wiki/Double_dabble */

    char *ptr = result;
    uint32_t reg;
    uint32_t i = 0;
    uint8_t digit;
    bool output;

    /* For 8 bits we can add the value to the shift register */
    reg = value;


    for (i=0; i < 8; ++i) {

        /* uint8_t max is 255 (3 digits). The first 8 bits of reg
           is used for the value 
        */
        if ((reg & 0x000F0000) >= 0x00050000) reg += 0x00030000;
        if ((reg & 0x0000F000) >= 0x00005000) reg += 0x00003000;
        if ((reg & 0x00000F00) >= 0x00000500) reg += 0x00000300;

        /* Shift */
        reg <<= 1;
    }

    // Collect
    output = false;

    digit = ((reg & 0x000F0000) >> 16); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg & 0x0000F000) >> 12); output |= (digit > 0); if (output) *ptr++ = ('0' + digit);
    digit = ((reg & 0x00000F00) >> 8 );                                    *ptr++ = ('0' + digit);

    *ptr++ = 0;

    return (ptr - result - 1);
}

static size_t enxtxt_conv_s8_to_dec_in_place(int8_t value, char *result)
{
    char *ptr = result;
    const int8_t mask = (value >> 31);
    const uint8_t absolute_value = ((value + mask) ^ mask);

    if (mask) {
        *ptr++ = '-';
    }

    return ((ptr - result) + enxtxt_conv_u16_to_dec_in_place(absolute_value, ptr));
}

static size_t enxtxt_conv_u32_to_hex_in_place(uint32_t value, char *result)
{
    *result++ = enxtxt_hex_digits[(value & 0xF0000000) >> 28];
    *result++ = enxtxt_hex_digits[(value & 0x0F000000) >> 24];
    *result++ = enxtxt_hex_digits[(value & 0x00F00000) >> 20];
    *result++ = enxtxt_hex_digits[(value & 0x000F0000) >> 16];
    *result++ = enxtxt_hex_digits[(value & 0x0000F000) >> 12];
    *result++ = enxtxt_hex_digits[(value & 0x00000F00) >> 8];
    *result++ = enxtxt_hex_digits[(value & 0x000000F0) >> 4];
    *result++ = enxtxt_hex_digits[(value & 0x0000000F) >> 0];
    *result++ = 0;

    return 8;
}

static size_t enxtxt_conv_u16_to_hex_in_place(uint16_t value, char *result)
{
    *result++ = enxtxt_hex_digits[(value & 0xF000) >> 12];
    *result++ = enxtxt_hex_digits[(value & 0x0F00) >> 8];
    *result++ = enxtxt_hex_digits[(value & 0x00F0) >> 4];
    *result++ = enxtxt_hex_digits[(value & 0x000F) >> 0];
    *result++ = 0;

    return 4;
}

static size_t enxtxt_conv_u8_to_hex_in_place(uint8_t value, char *result)
{
    *result++ = enxtxt_hex_digits[(value & 0x00F0) >> 4];
    *result++ = enxtxt_hex_digits[(value & 0x000F) >> 0];
    *result++ = 0;

    return 2;
}

struct enxtxt_conv_result enxtxt_conv_u32_to_dec(uint32_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_u32_to_dec_in_place(value, result.str);

    return result;
}

struct enxtxt_conv_result enxtxt_conv_s32_to_dec(int32_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_s32_to_dec_in_place(value, result.str);
    
    return result;
}

struct enxtxt_conv_result enxtxt_conv_u16_to_dec(uint16_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_u16_to_dec_in_place(value, result.str);

    return result;
}

struct enxtxt_conv_result enxtxt_conv_s16_to_dec(int16_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_s16_to_dec_in_place(value, result.str);
    
    return result;
}

struct enxtxt_conv_result enxtxt_conv_u8_to_dec(uint8_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_u16_to_dec_in_place(value, result.str);

    return result;
}

struct enxtxt_conv_result enxtxt_conv_s8_to_dec(int8_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_s8_to_dec_in_place(value, result.str);
    
    return result;
}

struct enxtxt_conv_result enxtxt_conv_u32_to_hex(uint32_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_u32_to_hex_in_place(value, result.str);
    
    return result;
}

struct enxtxt_conv_result enxtxt_conv_u16_to_hex(uint16_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_u16_to_hex_in_place(value, result.str);
    
    return result;
}

struct enxtxt_conv_result enxtxt_conv_u8_to_hex(uint8_t value)
{
    struct enxtxt_conv_result result;
    result.length = enxtxt_conv_u8_to_hex_in_place(value, result.str);
    
    return result;
}
