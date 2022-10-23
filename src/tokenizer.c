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

#include "tokenizer.h"

#include <string.h>


void enxtxt_tokenizer_init(
    struct enxtxt_tokenizer *obj,
    const char *ptr,
    size_t length) {

    obj->ptr = ptr;
    obj->index = -1;

    if (length) {
        obj->length = length;;

    } else {
        obj->length = strlen(ptr);
    }
}

bool enxtxt_tokenizer_get_next(
    struct enxtxt_tokenizer *obj,
    char delimiter,
    struct enxtxt_token *token) {

    if (obj->index == obj->length) {
        return false;
    }

    // Advance
    obj->index++;

    // Find the next delimiter
    token->ptr = (obj->ptr + obj->index);
    token->length = obj->index;
    while ((obj->index != obj->length) && (obj->ptr[obj->index] != delimiter)) {
        obj->index++;
    }

    token->length = (obj->index - token->length);
    token->final = (obj->index == obj->length);

    return true;
}
