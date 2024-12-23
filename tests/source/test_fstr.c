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

#include <enx/txt/fstr.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>


static void test_fstr_basic(void **state)
{
    (void)state;

    char buffer[1024];

    enxtxt_fstr_sz(
        buffer,
        sizeof(buffer),
        "one={}, two={}, three={}",
        f_int(-3),
        f_uint(3),
        f_h32(1234));

    puts(buffer);
}

static void test_fstr_floating_point(void **state)
{
    (void)state;

    char buffer[1024];

    enxtxt_fstr_sz(
        buffer,
        sizeof(buffer),
        "one={}, two={}",
        f_flt(0.53763f, 5),
        f_dbl(12.835, 3));

    puts(buffer);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_fstr_basic),
        cmocka_unit_test(test_fstr_floating_point)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
