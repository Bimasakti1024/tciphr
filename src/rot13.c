#include "ciphers.h"
#include "types.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

void rot13(cipher_data *data) {
	verbose = data->verbose;
	char *buffer = strdup(data->input);
	if (!buffer) {
		printf("Failed to allocate buffer\n");
		return;
	}

	for (int i = 0; buffer[i] != '\0'; i++) {
		if (!isalpha(buffer[i]))
			continue;
		char p = buffer[i];
		char c = shift_char(p, 13);
		buffer[i] = c;
		DBG_OUT("Shifted %c to %c\n", p, c)
	}

	puts(buffer);
	free(buffer);
}

void rot13_encode(cipher_data *data) { rot13(data); }
void rot13_decode(cipher_data *data) { rot13(data); }
