#include "../cipher/ciphers.h"
#include "../types.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *railfence_crack(cipher_data *data) {
	int len = strlen(data->input);
	int digitc = count_digits(len);

	data->key = calloc(1, digitc + 1);

	for (int i = 2; i <= len; i++) {
		snprintf(data->key, digitc + 1, "%d", i);

		char *buffer = railfence_decode(data);

		printf("%-*d Rail: %s\n", digitc, i, buffer);

		free(buffer);
	}

	free(data->key);
	return NULL;
}
