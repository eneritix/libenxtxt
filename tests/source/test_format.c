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
#include <inttypes.h>

#include <enx/txt/format.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

static void test_fmt_u64_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint64_t value = 0;
    do {
        result = enxtxt_fmt_u64_dec(value);
        sprintf(verification_result, "%"PRIu64"", value);

        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);


        value += 1099511627776;

    } while (value);
}

static void test_fmt_s64_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint64_t value = 0;
    do {
        result = enxtxt_fmt_s64_dec(value);
        sprintf(verification_result, "%"PRIi64"", (int64_t)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

        value += 1099511627776;

    } while (value);
}


static void test_fmt_u32_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint32_t value = 0;
    do {
        result = enxtxt_fmt_u32_dec(value);
        sprintf(verification_result, "%u", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

        value += 256;

    } while (value);
}

static void test_fmt_s32_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint32_t value = 0;
    do {
        result = enxtxt_fmt_s32_dec(value);
        sprintf(verification_result, "%d", (int)((int32_t)value));
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

        value += 256;

    } while (value);
}

static void test_fmt_u16_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint16_t value = 0;
    do {
        value--;
        result = enxtxt_fmt_u16_dec(value);
        sprintf(verification_result, "%u", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_fmt_s16_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint16_t value = 0;
    do {
        value--;
        result = enxtxt_fmt_s16_dec(value);
        sprintf(verification_result, "%d", (int)((int16_t)value));
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_fmt_u8_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint8_t value = 0;
    do {
        value--;
        result = enxtxt_fmt_u8_dec(value);
        sprintf(verification_result, "%u", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_fmt_s8_dec(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint8_t value = 0;
    do {
        value--;
        result = enxtxt_fmt_s8_dec(value);
        sprintf(verification_result, "%d", (int)((int8_t)value));
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_fmt_u32_hex(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint32_t value = 0;
    do {
        result = enxtxt_fmt_u32_hex(value);
        sprintf(verification_result, "%08X", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);
        value += 256;

    } while (value);
}

static void test_fmt_u16_hex(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint16_t value = 0;
    do {
        value--;
        result = enxtxt_fmt_u16_hex(value);
        sprintf(verification_result, "%04X", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

static void test_fmt_u8_hex(void **state)
{
    (void)state;
    struct enxtxt_fmt_result result;
    char verification_result[24];

    uint8_t value = 0;
    do {
        value--;
        result = enxtxt_fmt_u8_hex(value);
        sprintf(verification_result, "%02X", (unsigned int)value);
        assert_true(strcmp(result.str, verification_result) == 0);
        assert_true(strlen(result.str) == result.length);

    } while (value);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_fmt_u64_dec),
        cmocka_unit_test(test_fmt_s64_dec),
        cmocka_unit_test(test_fmt_u32_dec),
        cmocka_unit_test(test_fmt_s32_dec),
        cmocka_unit_test(test_fmt_u16_dec),
        cmocka_unit_test(test_fmt_s16_dec),
        cmocka_unit_test(test_fmt_u8_dec),
        cmocka_unit_test(test_fmt_s8_dec),
        cmocka_unit_test(test_fmt_u32_hex),
        cmocka_unit_test(test_fmt_u16_hex),
        cmocka_unit_test(test_fmt_u8_hex)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
