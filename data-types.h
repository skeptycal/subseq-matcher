/*
 * Copyright (C) 2017 Kovid Goyal <kovid at kovidgoyal.net>
 *
 * Distributed under terms of the GPL3 license.
 */

#pragma once
#if defined(_MSC_VER)
#define ISWINDOWS
#ifndef ssize_t
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#endif
#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "vector.h"
#include "cli.h"

typedef struct gengetopt_args_info args_info;

typedef uint8_t len_t;
typedef uint32_t text_t;

#define LEN_MAX UINT8_MAX
#define UNUSED(x) (void)(x)
#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

typedef struct {
    text_t* src;
    ssize_t src_sz;
    len_t haystack_len;
    len_t *positions;
    double score;
    ssize_t idx;
} Candidate;

typedef struct {
    Candidate *haystack;
    size_t haystack_count;
    text_t level1[LEN_MAX], level2[LEN_MAX], level3[LEN_MAX], needle[LEN_MAX];
    len_t level1_len, level2_len, level3_len, needle_len;
    size_t haystack_size;
} GlobalData;

VECTOR_OF(len_t, Positions)
VECTOR_OF(text_t, Chars)
VECTOR_OF(Candidate, Candidates)


void output_results(Candidate *haystack, size_t count, args_info *opts, len_t needle_len);
void* alloc_workspace(len_t max_haystack_len, GlobalData*);
void* free_workspace(void *v);
double score_item(void *v, text_t *haystack, len_t haystack_len, len_t *match_positions);
size_t decode_string(char *src, size_t sz, text_t *dest);
unsigned int encode_codepoint(text_t ch, char* dest);
size_t unescape(char *src, char *dest, size_t destlen);
int cpu_count();
void* alloc_threads(size_t num_threads);
bool start_thread(void* threads, size_t i, void *(*start_routine) (void *), void *arg);
void wait_for_thread(void *threads, size_t i);
void free_threads(void *threads);
