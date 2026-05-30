#include "ciphers.h"
#include "types.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

void atbash(cipher_data *data) {
	verbose = data->verbose;
	char *buffer = strdup(data->input);
	if (!buffer) {
		printf("Failed to allocate buffer\n");
		return;
	}

	for (int i = 0; buffer[i] != '\0'; i++) {
		if (!isalpha(buffer[i]))
			continue;
		char c = tolower(buffer[i]) - 'a';
		c = 25 - c;
		if (isupper(buffer[i]))
			c += 'A';
		else
			c += 'a';
		DBG_OUT("Shifted %c to %c\n", buffer[i], c)
		buffer[i] = c;
	}

	puts(buffer);
	free(buffer);
}

void atbash_encode(cipher_data *data) { atbash(data); }
void atbash_decode(cipher_data *data) { atbash(data); }
