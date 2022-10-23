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

#include <enx/txt/tokenizer.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>


static void test_tokenizer_single_token(void **state)
{
    (void)state;

    const char *str = "token";

    struct enxtxt_tokenizer tokenizer;
    enxtxt_tokenizer_init(&tokenizer, str, 0);

    struct enxtxt_token tokens[1];
    int token_index = 0;

    while (enxtxt_tokenizer_get_next(&tokenizer, ',', &tokens[token_index])) {
        token_index++;
    }

    assert_true(token_index == 1);
    assert_true(tokens[0].length == 5);
    assert_true(tokens[0].final == true);

}

static void test_tokenizer_empty_string(void **state)
{
    (void)state;

    const char *str = "";

    struct enxtxt_tokenizer tokenizer;
    enxtxt_tokenizer_init(&tokenizer, str, 0);

    struct enxtxt_token tokens[1];
    int token_index = 0;

    while (enxtxt_tokenizer_get_next(&tokenizer, ',', &tokens[token_index])) {
        token_index++;
    }

    assert_true(token_index == 1);
    assert_true(tokens[0].length == 0);
    assert_true(tokens[0].final == true);

}


static void test_tokenizer_empty_tokens(void **state)
{
    (void)state;

    const char *str = ",,";

    struct enxtxt_tokenizer tokenizer;
    enxtxt_tokenizer_init(&tokenizer, str, 0);

    struct enxtxt_token tokens[3];
    int token_index = 0;

    while (enxtxt_tokenizer_get_next(&tokenizer, ',', &tokens[token_index])) {
        token_index++;
    }

    assert_true(token_index == 3);
    assert_true(tokens[0].length == 0);
    assert_true(tokens[0].final == false);
    assert_true(tokens[1].length == 0);
    assert_true(tokens[1].final == false);
    assert_true(tokens[2].length == 0);
    assert_true(tokens[2].final == true);
}

static void test_tokenizer_empty_start(void **state)
{
    (void)state;

    const char *str = ",two,three";

    struct enxtxt_tokenizer tokenizer;
    enxtxt_tokenizer_init(&tokenizer, str, 0);

    struct enxtxt_token tokens[3];
    int token_index = 0;

    while (enxtxt_tokenizer_get_next(&tokenizer, ',', &tokens[token_index])) {
        token_index++;
    }

    assert_true(token_index == 3);
    assert_true(tokens[0].length == 0);
    assert_true(tokens[0].final == false);
    assert_true(tokens[1].length == 3);
    assert_true(tokens[1].final == false);
    assert_true(tokens[2].length == 5);
    assert_true(tokens[2].final == true);
}

static void test_tokenizer_empty_end(void **state)
{
    (void)state;

    const char *str = "two,three,";

    struct enxtxt_tokenizer tokenizer;
    enxtxt_tokenizer_init(&tokenizer, str, 0);

    struct enxtxt_token tokens[3];
    int token_index = 0;

    while (enxtxt_tokenizer_get_next(&tokenizer, ',', &tokens[token_index])) {
        token_index++;
    }

    assert_true(token_index == 3);
    assert_true(tokens[0].length == 3);
    assert_true(tokens[0].final == false);
    assert_true(tokens[1].length == 5);
    assert_true(tokens[1].final == false);
    assert_true(tokens[2].length == 0);
    assert_true(tokens[2].final == true);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_tokenizer_single_token),
        cmocka_unit_test(test_tokenizer_empty_string),
        cmocka_unit_test(test_tokenizer_empty_tokens),
        cmocka_unit_test(test_tokenizer_empty_start),
        cmocka_unit_test(test_tokenizer_empty_end)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
