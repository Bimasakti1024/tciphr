#include "../types.h"
#include "../util.h"
#include "ciphers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

char *caesar_shift(cipher_data *data, int shift) {
	verbose = data->verbose;
	char *buffer = strdup(data->input);
	if (!buffer) {
		fprintf(stderr, "Failed to allocate buffer\n");
		return NULL;
	}
	for (int i = 0; data->input[i] != '\0'; i++) {
		char c = shift_char(data->input[i], shift);
		buffer[i] = c;
		DBG_OUT("Shifted %c to %c", data->input[i], c)
	}

	return buffer;
}

char *caesar_encode(cipher_data *data) {
	return caesar_shift(data, atoi(data->key));
}
char *caesar_decode(cipher_data *data) {
	return caesar_shift(data, -atoi(data->key));
}
