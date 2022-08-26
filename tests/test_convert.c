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


static void test_dec_str_to_s32(void **state)
{
    assert_true(enxtxt_dec_to_s32_nt("0") == 0);
    assert_true(enxtxt_dec_to_s32_nt("-1") == -1);
    assert_true(enxtxt_dec_to_s32_nt("2147483647") == 2147483647);
    assert_true(enxtxt_dec_to_s32_nt("-2147483648") == -2147483648);
}

static void test_dec_str_to_u32(void **state)
{
    assert_true(enxtxt_dec_to_u32_nt("0") == 0);
    assert_true(enxtxt_dec_to_u32_nt("16384") == 16384);
    assert_true(enxtxt_dec_to_u32_nt("4294967295") == 4294967295);
}

static void test_hex_str_to_u32(void **state)
{
    assert_true(enxtxt_hex_to_u32_nt("0x00000000") == 0x00000000);
    assert_true(enxtxt_hex_to_u32_nt("0xFFFFFFFF") == 0xFFFFFFFF);
    assert_true(enxtxt_hex_to_u32_nt("0xABCDEF12") == 0xABCDEF12);
    assert_true(enxtxt_hex_to_u32_nt("0xabcdef12") == 0xABCDEF12);

    assert_true(enxtxt_hex_to_u32_nt("00000000") == 0x00000000);
    assert_true(enxtxt_hex_to_u32_nt("FFFFFFFF") == 0xFFFFFFFF);
    assert_true(enxtxt_hex_to_u32_nt("ABCDEF12") == 0xABCDEF12);
    assert_true(enxtxt_hex_to_u32_nt("abcdef12") == 0xABCDEF12);

    assert_true(enxtxt_hex_to_u32_nt("00000001") == 0x00000001);
    assert_true(enxtxt_hex_to_u32_nt("0000000A") == 0x0000000A);
    assert_true(enxtxt_hex_to_u32_nt("0000000a") == 0x0000000a);
    assert_true(enxtxt_hex_to_u32_nt("0000000F") == 0x0000000F);
    assert_true(enxtxt_hex_to_u32_nt("0000000f") == 0x0000000F);
}

static void test_hex_to_u8_array(void **state)
{
    {
        const char *input = "00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f";
        uint8_t result[16];
        uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

        size_t length = enxtxt_hex_to_u8_array_pl(input, strlen(input), result, sizeof(result));

        assert_true(length == 16);
        assert_true(memcmp(result, expected, sizeof(result)) == 0);
    }

    {
        const char *input = "000102030405060708090a0b0c0d0e0f";
        uint8_t result[16];
        uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

        size_t length = enxtxt_hex_to_u8_array_pl(input, strlen(input), result, sizeof(result));

        assert_true(length == 16);
        assert_true(memcmp(result, expected, sizeof(result)) == 0);
    }
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_dec_str_to_s32),
        cmocka_unit_test(test_dec_str_to_u32),
        cmocka_unit_test(test_hex_str_to_u32),
        cmocka_unit_test(test_hex_to_u8_array)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
