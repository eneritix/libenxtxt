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

#ifndef ENXTXT_TOKENIZER_H
#define ENXTXT_TOKENIZER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/**
 * @brief Tokenizer
 */
struct enxtxt_tokenizer
{
    const char *ptr;
    ssize_t length;
    ssize_t index;
};

/**
 * @brief Token
 */
struct enxtxt_token
{
    const char *ptr;
    size_t length;
    bool final;
};

/**
 * @brief Initializes a tokenizer
 */
void enxtxt_tokenizer_init(
    struct enxtxt_tokenizer *obj,
    const char *ptr,
    size_t length);

/**
 * @brief Retrieves the next token
 * @returns true if a token was available
 */
bool enxtxt_tokenizer_get_next(
    struct enxtxt_tokenizer *obj,
    char delimiter,
    struct enxtxt_token *token);


__END_DECLS

#endif
