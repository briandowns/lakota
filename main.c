/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2021 Brian J. Downs
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "words.h"

#define STR1(x) #x
#define STR(x) STR1(x)

#define USAGE                                                        \
    "usage: %s [-vh]\n"                                              \
    "  -l            english translation of the given Lakota word\n" \
    "  -p            pronunciation for the given Lakota word\n"      \
    "  -s            search for similar words for a given string\n"  \
    "  -v            version\n"                                      \
    "  -h            help\n"

int
main(int argc, char **argv)
{
    if (argc == 1) {
        printf(USAGE, STR(bin_name));
    }
    
    int opt;
    
    while ((opt = getopt(argc, argv, "l:p:s:vh")) != -1) {
        switch (opt) {
            case 'l':
                for (int i = 0; i < WORD_COUNT; i++) {
                    if (strcmp(optarg, words_dictionary[i].lakota) == 0) {
                        printf("%s\n", words_dictionary[i].english);
                    }
                }
                break;
            case 'p':
                for (int i = 0; i < WORD_COUNT; i++) {
                    if (strcmp(optarg, words_dictionary[i].lakota) == 0) {
                        printf("%s\n", words_dictionary[i].pronunciation);
                        break;
                    }
                }
                break;
            case 's':
                for (int i = 0; i < WORD_COUNT; i++) {
                    int res = words_match(optarg, strlen(optarg), 
                        words_dictionary[i].lakota, 
                        strlen(words_dictionary[i].lakota));
                    if (res > 1 && res < 3) {
                        printf("%s\n", words_dictionary[i].lakota);
                    }
                }
                break;                
            case 'v':
                printf("version: %s - git: %s\n", STR(app_version), STR(git_sha));
                break;
            case 'h':
                printf(USAGE, STR(bin_name));
                break;
        }
    }

    return 0;
}
