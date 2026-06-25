#include "frequency.h"
#include "util.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int find_char_occurence(const char *s, char c) {
	int o = 0;

	for (int i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			o++;

	return o;
}

float index_of_coincidence(const char *s) {
	char *cleaned = strip_non_alpha(s);
	char freq[26] = {0};
	int len = strlen(cleaned);

	// Count frequency
	for (int i = 0; i < len; i++) {
		if ((cleaned[i]))
			freq[tolower(cleaned[i]) - 'a']++;
	}

	// Count numerator
	float numerator = 0;
	for (int i = 0; i < 26; i++)
		numerator += freq[i] * (freq[i] - 1);

	// Count denominator
	float denominator = len * (len - 1);

	free(cleaned);
	return numerator / denominator;
}
