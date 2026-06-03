#include "ciphers.h"
#include "types.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

char *vigenere_shift(cipher_data *data, int encrypt) {
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
			int shift = tolower(data->key[WRAP(key_pos, key_len)]) - 'a';
			c = shift_char(c, encrypt * shift);
			key_pos++;
			DBG_OUT("Shifted %c with key %c to %c\n", data->input[i], c, shift)
		} else {
			DBG_OUT("Ignored \'%c\': not an alphabetic character\n", c)
		}
		buffer[i] = c;
	}

	return buffer;
}

char *vigenere_encode(cipher_data *data) { return vigenere_shift(data, 1); }
char *vigenere_decode(cipher_data *data) { return vigenere_shift(data, -1); }
