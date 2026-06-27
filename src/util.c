#include "util.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char shift_char(char c, int shift) {
	if (islower(c))
		c = (char)('a' + WRAP(((int)c - 'a') + shift, 26));
	else if (isupper(c))
		c = (char)('A' + WRAP(((int)c - 'A') + shift, 26));
	return c;
}

int search_non_alpha(const char *str) {
	int c = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isalpha(str[i])) {
			c++;
		}
	}
	return c;
}

char *strip_non_alpha(const char *str) {
	int p = 0;
	char *s = strdup(str);
	memset(s, 0, strlen(s));

	for (int i = 0; i < strlen(str); i++) {
		if (isalpha(str[i])) {
			s[p++] = str[i];
		}
	}
	return s;
}

char *repeated_char(char c, int l) {
	if (l <= 0)
		return strdup("");

	char *r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return strdup("");
	for (int i = 0; i < l; i++)
		r[i] = c;
	r[l] = '\0';
	return r;
}

void repeated_char_out(char c, int l) {
	if (l <= 0)
		return;

	char *r = repeated_char(c, l);
	if (r)
		printf("%s", r);
	free(r);
	return;
}

char **split_chunk(const char *str, int chunk_size, int chunkc) {
	char **buffer = calloc(chunkc, sizeof(char *));
	if (!buffer)
		return NULL;

	int len = strlen(str);
	int chunkp = 0;
	for (int i = 0; i < len; i += chunk_size) {
		int size = (len - i < chunk_size) ? len - i : chunk_size;

		// Initiate chunk
		buffer[chunkp] = calloc(chunk_size + 1, sizeof(char));

		memcpy(buffer[chunkp], str + i, size);

		buffer[chunkp][size] = '\0';
		chunkp++;
	}

	return buffer;
}

int count_digits(long long n) {
	int count = 0;

	n = llabs(n);

	do {
		n /= 10;
		count++;
	} while (n != 0);

	return count;
}

char *readline_file(FILE *f) {
	size_t len = 0, cap = 128;
	char *buf = malloc(cap);
	if (!buf)
		return NULL;

	char c;
	while ((c = fgetc(f)) != EOF && c != '\n') {
		if (len + 1 >= cap) {
			cap *= 2;
			char *tmp = realloc(buf, cap);
			if (!tmp) {
				free(buf);
				return NULL;
			}
			buf = tmp;
		}
		buf[len++] = c;
	}

	if (len == 0 && c == EOF) {
		free(buf);
		return NULL;
	}

	buf[len] = '\0';
	return buf;
}

int gcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}
