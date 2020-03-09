// Copyright 2020 All Rights Reserved.
// Author: 
#ifndef  STRING_SIMD_H_
#define  STRING_SIMD_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <emmintrin.h>
// base code from
// https://github.com/laruence/stashes/blob/master/replace_chr.c
//
static inline unsigned long long rdtsc(void) {
	unsigned int hi, lo;
	__asm__ __volatile__("rdtsc;rdtsc;\n" : "=a"(lo), "=d"(hi));

	return (unsigned long long)lo | ((unsigned long long)hi << 32);
}

static inline void replace_chr_normal(char *class_name, size_t class_name_len, char ac, char des) {
	char *pos = class_name;
	size_t len = class_name_len;

	while ((pos = (char*)memchr(pos, ac, len - (pos - class_name)))) {
		*pos++ = des;
	}
	return;
}

static inline void replace_chr_sse2(char *class_name, size_t class_name_len, char ac, char des) {
	char *pos = class_name;
	size_t len = class_name_len;

	const __m128i slash = _mm_set1_epi8(ac);
	const __m128i delta = _mm_set1_epi8(des - ac);

	while (len >= 16) {
		__m128i op = _mm_loadu_si128((__m128i *)pos);
		__m128i eq = _mm_cmpeq_epi8(op, slash);
		if (_mm_movemask_epi8(eq)) {
			eq = _mm_and_si128(eq, delta);
			op = _mm_add_epi8(op, eq);
			_mm_storeu_si128((__m128i*)pos, op);
		}
		len -= 16;
		pos += 16;
	}

	return replace_chr_normal(pos, len, ac, des);
}

static bool find_chr_normal(char* class_name, size_t class_name_len, char ac) {
	char *pos = class_name;
	size_t len = class_name_len;
    return memchr(pos, ac, len - (pos - class_name)) != NULL;
}

static bool find_chr_sse2(char* class_name, size_t class_name_len, char ac) {
	char *pos = class_name;
	size_t len = class_name_len;

	const __m128i slash = _mm_set1_epi8(ac);

	while (len >= 16) {
		__m128i op = _mm_loadu_si128((__m128i *)pos);
		__m128i eq = _mm_cmpeq_epi8(op, slash);
		if (_mm_movemask_epi8(eq)) {
            return true;
		}
		len -= 16;
		pos += 16;
	}

	return find_chr_normal(pos, len, ac);
}

static inline void bench_replace_normal(char *mem, int step) {
	unsigned long long int s;
	int i;

	// Warmup
	replace_chr_normal(mem, 1, '\\', '-');

	s = rdtsc();
	for (i = step; i <= 1024; i += step) {
		replace_chr_normal(mem, step, '\\', '-');
		mem += step;
	}
	printf("replace_chr_normal on %4d bytes cost %4lld ticks\n", step, rdtsc() - s);
}

static inline void bench_replace_sse2(char *mem, int step) {
	unsigned long long int s;
	int i;

	// Warmup
	replace_chr_sse2(mem, 1, '\\', '-');

	s = rdtsc();
	for (i = step; i <= 1024; i += step) {
		replace_chr_sse2(mem, step, '\\', '-');
		mem += step;
	}
	printf("replace_chr_sse2   on %4d bytes cost %4lld ticks\n", step, rdtsc() - s);
}

static inline void bench_find_normal(char *mem, int step) {
	unsigned long long int s;
	int i;

	// Warmup
	find_chr_normal(mem, 1, '\\');

	s = rdtsc();
	for (i = step; i <= 1024; i += step) {
		find_chr_normal(mem, step, '\\');
		mem += step;
	}
	printf("find_chr_normal on %4d bytes cost %4lld ticks\n", step, rdtsc() - s);
}

static inline void bench_find_sse2(char *mem, int step) {
	unsigned long long int s;
	int i;

	// Warmup
	find_chr_sse2(mem, 1, '\\');

	s = rdtsc();
	for (i = step; i <= 1024; i += step) {
		find_chr_sse2(mem, step, '\\');
		mem += step;
	}
	printf("find_chr_sse2   on %4d bytes cost %4lld ticks\n", step, rdtsc() - s);
}

static const char ascii[] = "01234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\\_+_^%$#@!";

static char* prepare_string(int capacity) {
	char *str = (char*)malloc(sizeof(char) * capacity);
	srand(time(NULL));
	for (int i = 0; i < capacity; i++) {
		str[i] = ascii[rand() % (sizeof(ascii) - 1)];
	}
	return str;
}

int main(int argc, char **argv) {
	int capacity = 1024 * 1024;
	char *str = prepare_string(capacity);
	char *dup = strndup(str, capacity);

	bench_replace_sse2(str, 8);
	memcpy(str, dup, capacity);
	bench_replace_normal(str, 8);
	memcpy(str, dup, capacity);
	bench_replace_sse2(str, 16);
	memcpy(str, dup, capacity);
	bench_replace_normal(str, 16);
	memcpy(str, dup, capacity);
	bench_replace_sse2(str, 32);
	memcpy(str, dup, capacity);
	bench_replace_normal(str, 32);
	memcpy(str, dup, capacity);
	bench_replace_sse2(dup, 64);
	bench_replace_normal(str, 64);

	if (memcmp(str, dup, capacity) == 0) {
		printf("result is the same\n");
	} else {
		printf("result is different\n");
	}

	bench_find_sse2(str, 8);
	memcpy(str, dup, capacity);
	bench_find_normal(str, 8);
	memcpy(str, dup, capacity);
	bench_find_sse2(str, 16);
	memcpy(str, dup, capacity);
	bench_find_normal(str, 16);
	memcpy(str, dup, capacity);
	bench_find_sse2(str, 32);
	memcpy(str, dup, capacity);
	bench_find_normal(str, 32);
	memcpy(str, dup, capacity);

	bench_find_sse2(str, 64);
	memcpy(str, dup, capacity);
	bench_find_normal(str, 64);
	memcpy(str, dup, capacity);

	bench_find_sse2(str, 128);
	memcpy(str, dup, capacity);
	bench_find_normal(str, 128);
	memcpy(str, dup, capacity);

	bench_find_sse2(str, 256);
	memcpy(str, dup, capacity);
	bench_find_normal(str, 256);
	memcpy(str, dup, capacity);

	bench_find_sse2(dup, 512);
	bench_find_normal(str, 512);

	free(str);
	free(dup);
	return 0;
}

#endif  // STRING_SIMD_H_
