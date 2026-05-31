#include "ciphers.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

void autokey_encode(cipher_data *data) {
	verbose = data->verbose;
	char *buffer = strdup(data->input);
	if (!buffer) {
		printf("Failed to allocate buffer\n");
		return;
	}
	int plainlen = strlen(buffer);
	int keylen = strlen(data->key);

	char keystream[plainlen + 1];
	memset(keystream, 0, sizeof(keystream));

	// Generate keystream
	for (int i = 0; i < plainlen; i++) {
		int p = i;
		char c;
		if (keylen > i) {
			c = data->key[p];
		} else {
			p = p - keylen;
			c = buffer[p];
		}
		keystream[i] = c;
	}

	DBG_OUT("Generated keystream: %s\n", keystream)

	// Shift each character
	for (int i = 0; i < plainlen; i++) {
		int shift = tolower(keystream[i]) - 'a';
		int c = shift_char(buffer[i], shift);
		DBG_OUT("Shifted %c with key %c to %c\n", buffer[i], keystream[i], c)
		buffer[i] = c;
	}
	puts(buffer);
	free(buffer);
}

void autokey_decode(cipher_data *data) {}
