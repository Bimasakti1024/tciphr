#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define WRAP(x, n) (((x) % (n) + (n)) % (n))
#define DBG_OUT(msg, ...)                                                      \
	if (verbose)                                                               \
		printf(msg, ##__VA_ARGS__);

char shift_char(char c, int shift);
int search_non_alpha(const char *str);
char *strip_non_alpha(const char *str);
char *repeated_char(char c, int l);
void repeated_char_out(char c, int l);
char **split_chunk(const char *str, int chunk_size, int chunkc);
int count_digits(long long n);
char *readline_file(FILE *f);
int gcd(int a, int b);
int find_char_occurence(const char *s, char c);

#endif
