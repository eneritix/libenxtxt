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

#include <stdio.h>
#include <stdbool.h>

#include <enx/txt/convert.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>


static void test_conv_u32_to_dec(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint32_t value = 0;
    do {
        result = enxtxt_conv_u32_to_dec(value);
        sprintf(verification_result, "%u", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

        value += 256;

    } while (value);
}

static void test_conv_s32_to_dec(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint32_t value = 0;
    do {
        result = enxtxt_conv_s32_to_dec(value);
        sprintf(verification_result, "%d", (int)((int32_t)value));
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

        value += 256;

    } while (value);
}

static void test_conv_u16_to_dec(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint16_t value = 0;
    do {
        value--;
        result = enxtxt_conv_u16_to_dec(value);
        sprintf(verification_result, "%u", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_conv_s16_to_dec(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint16_t value = 0;
    do {
        value--;
        result = enxtxt_conv_s16_to_dec(value);
        sprintf(verification_result, "%d", (int)((int16_t)value));
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_conv_u8_to_dec(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint8_t value = 0;
    do {
        value--;
        result = enxtxt_conv_u8_to_dec(value);
        sprintf(verification_result, "%u", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_conv_s8_to_dec(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint8_t value = 0;
    do {
        value--;
        result = enxtxt_conv_s8_to_dec(value);
        sprintf(verification_result, "%d", (int)((int8_t)value));
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_conv_u32_to_hex(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint32_t value = 0;
    do {
        result = enxtxt_conv_u32_to_hex(value);
        sprintf(verification_result, "%08X", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);
        value += 256;

    } while (value);
}

static void test_conv_u16_to_hex(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint16_t value = 0;
    do {
        value--;
        result = enxtxt_conv_u16_to_hex(value);
        sprintf(verification_result, "%04X", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_conv_u8_to_hex(void **state)
{
    (void)state;
    struct enxtxt_conv_result result;
    char verification_result[24];

    uint8_t value = 0;
    do {
        value--;
        result = enxtxt_conv_u8_to_hex(value);
        sprintf(verification_result, "%02X", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_conv_u32_to_dec),
        cmocka_unit_test(test_conv_s32_to_dec),
        cmocka_unit_test(test_conv_u16_to_dec),
        cmocka_unit_test(test_conv_s16_to_dec),
        cmocka_unit_test(test_conv_u8_to_dec),
        cmocka_unit_test(test_conv_s8_to_dec),
        cmocka_unit_test(test_conv_u32_to_hex),
        cmocka_unit_test(test_conv_u16_to_hex),
        cmocka_unit_test(test_conv_u8_to_hex)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
