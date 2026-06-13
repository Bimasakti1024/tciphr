#include "../types.h"
#include "../util.h"
#include "ciphers.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

char *beaufort(cipher_data *data) {
	verbose = data->verbose;
	char *buffer = strdup(data->input);
	if (!buffer) {
		printf("Failed to allocate buffer\n");
		return NULL;
	}

	if (search_non_alpha(data->key)) {
		printf("Key contains a non alphabetic character\n");
		free(buffer);
		return NULL;
	}

	size_t key_len = strlen(data->key);
	int key_pos = 0;
	for (int i = 0; data->input[i] != '\0'; i++) {
		char c = data->input[i];
		if (isalpha(c)) {
			char p = c - 'a';
			int k = tolower(data->key[WRAP(key_pos, key_len)]) - 'a';

			// Beaufort formula
			/// If K - P is negative will add 26 to it
			c = k - p;
			if (c < 0)
				c += 26;
			c = (c % 26) + 'a';

			// Keep case
			if (isupper(data->input[i]))
				c = toupper(c);

			DBG_OUT("Shifted %c with key %c to %c\n", data->input[i], k + 'a',
					c)
			key_pos++;
		} else {
			DBG_OUT("Ignored \'%c\': not an alphabetic character\n",
					data->input[i])
		}
		buffer[i] = c;
	}

	return buffer;
}

char *beaufort_encode(cipher_data *data) { return beaufort(data); }
char *beaufort_decode(cipher_data *data) { return beaufort(data); }
