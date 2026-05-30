#include "ciphers.h"
#include "types.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

static void caesar_shift(cipher_data *data, int shift) {
	verbose = data->verbose;
	char *buffer = strdup(data->input);
	if (!buffer) {
		printf("Failed to allocate buffer\n");
		return;
	}
	for (int i = 0; data->input[i] != '\0'; i++) {
		char c = shift_char(data->input[i], shift);
		buffer[i] = c;
		DBG_OUT("Shifted %c to %c", data->input[i], c)
	}
	puts(buffer);
	free(buffer);
}

void caesar_encode(cipher_data *data) { caesar_shift(data, atoi(data->key)); }
void caesar_decode(cipher_data *data) { caesar_shift(data, -atoi(data->key)); }
