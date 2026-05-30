#include "util.h"
#include <ctype.h>
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
	int len = strlen(str);
	char *stripped = malloc(len + 1);
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (isalpha(str[i])) {
			stripped[j++] = str[i];
		}
	}
	stripped[j] = '\0';
	return stripped;
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
