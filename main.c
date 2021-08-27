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

#define USAGE                                                    \
    "usage: %s [-vh]\n"                                          \
    "  -l        English translation of the given Lakota word\n" \
    "  -e        Lakota translation of the given English word\n" \
    "  -p        pronunciation for the given Lakota word\n"      \
    "  -f        fuzzy search for similar words to the given\n"  \
    "  -v        version\n"                                      \
    "  -h        help\n"

#define SEARCH_LAKOTA  1
#define SEARCH_ENGLISH 2
#define PRONUNCIATION  3

#define SEARCH(sl, pl) if (fuzzy) {                      \
    for (int i = 0; i < WORD_COUNT; i++) {               \
        if (strstr(words_dictionary[i].sl, word)) {      \
            printf("%s (%s)\n", words_dictionary[i].sl,  \
                words_dictionary[i].pl);                 \
        }                                                \
    }                                                    \
    break;                                               \
    }                                                    \
    for (int i = 0; i < WORD_COUNT; i++) {               \
        if (strcmp(word, words_dictionary[i].sl) == 0) { \
            printf("%s\n", words_dictionary[i].pl);      \
            break;                                       \
        }                                                \
    }

int
main(int argc, char **argv)
{
    if (argc == 1) {
        printf(USAGE, STR(bin_name));
        return 1;
    }

    int opt;
    int operation, fuzzy = 0;
    char *word;
    
    while ((opt = getopt(argc, argv, "fl:e:p:vh")) != -1) {
        switch (opt) {
            case 'l':
                operation = SEARCH_LAKOTA;
                word = strdup(optarg);
                break;
            case 'e':
                operation = SEARCH_ENGLISH;
                word = strdup(optarg);
                break;
            case 'p':
                operation = PRONUNCIATION;
                word = strdup(optarg);
                break;
            case 'f':
                fuzzy = 1;
                break;                
            case 'v':
                printf("version: %s - git: %s\n", STR(app_version), STR(git_sha));
                return 0;
            case 'h':
                printf(USAGE, STR(bin_name));
                return 0;
            default:
                printf(USAGE, STR(bin_name));
                return 0;
        }
    }

    switch(operation) {
        case SEARCH_LAKOTA:
            // if (fuzzy) {
            //     for (int i = 0; i < WORD_COUNT; i++) {
            //         if (strstr(word, words_dictionary[i].lakota)) {
            //             printf("%s (%s)\n", words_dictionary[i].english, 
            //                 words_dictionary[i].lakota);
            //         }
            //     }
            //     break;
            // } 
            // for (int i = 0; i < WORD_COUNT; i++) {
            //     if (strcmp(word, words_dictionary[i].lakota) == 0) {
            //         printf("%s\n", words_dictionary[i].english);
            //         break;
            //     }
            // }
            SEARCH(lakota, english);
            break;
        case SEARCH_ENGLISH:
            // if (fuzzy) {
            //     for (int i = 0; i < WORD_COUNT; i++) {
            //         if (strstr(word, words_dictionary[i].english)) {
            //             printf("%s (%s) - %s\n", words_dictionary[i].lakota, 
            //                 words_dictionary[i].pronunciation, 
            //                 words_dictionary[i].english);
            //         }
            //     }
            //     break;
            // }
            // for (int i = 0; i < WORD_COUNT; i++) {
            //     if (strcmp(word, words_dictionary[i].english) == 0) {
            //         printf("%s (%s)\n", words_dictionary[i].lakota, 
            //             words_dictionary[i].pronunciation);
            //     }
            // }
            SEARCH(english, lakota);
            break;
        case PRONUNCIATION:
            for (int i = 0; i < WORD_COUNT; i++) {
                if (strcmp(word, words_dictionary[i].lakota) == 0) {
                    printf("%s\n", words_dictionary[i].pronunciation);
                    break;
                }
            }
    }

    free(word);
    
    return 0;
}
