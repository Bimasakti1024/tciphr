#include "ciphers.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

void autokey_encode(cipher_data *data) {
	verbose = data->verbose;
	char *plaintext = strdup(data->input);
	int plainlen = strlen(plaintext);
	int keylen = strlen(data->key);

	char keystream[plainlen];
	memset(keystream, 0, sizeof(keystream));

	// Generate keystream
	for (int i = 0; i < plainlen; i++) {
		int p = i;
		char c;
		if (keylen > i) {
			c = data->key[p];
		} else {
			p = p - keylen;
			c = plaintext[p];
		}
		keystream[i] = c;
	}

	DBG_OUT("Generated keystream: %s\n", keystream)
	free(plaintext);
}

void autokey_decode(cipher_data *data) {}
