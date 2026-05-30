#include "ciphers.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

void railfence_encode(cipher_data *data) {
	verbose = data->verbose;

	char *plaintext = strip_non_alpha(data->input);
	size_t plainlen = strlen(plaintext);
	if (strcmp(plaintext, data->input))
		DBG_OUT("Stripped non-alphabetic characters from plaintext: %s to %s\n",
				data->input, plaintext)

	int railc = atoi(data->key);
	if (railc <= 1) {
		printf("Rail count must at least be 2\n");
		exit(EXIT_FAILURE);
	}

	// 2D matrix with railc row and plainlen col
	char rails[railc][plainlen];
	int railp[railc];
	memset(railp, 0, sizeof(railp));
	memset(rails, 0, sizeof(rails));

	int rail = 0;
	int direction = 1;
	for (int i = 0; plaintext[i] != '\0'; i++) {
		rails[rail][railp[rail]++] = plaintext[i];

		rail += direction;

		// Direction swapping
		if (rail == 0 || rail == railc - 1)
			direction = -direction;
	}

	char output[plainlen + 1];
	int pos = 0;
	for (int i = 0; i < railc; i++) {
		DBG_OUT("Rail %d: %s\n", i, rails[i])
		for (int j = 0; j < railp[i]; j++) {
			output[pos++] = rails[i][j];
		}
	}
	output[pos] = '\0';
	puts(output);
	free(plaintext);
}

void railfence_decode(cipher_data *data) {
	verbose = data->verbose;

	char *ciphertext = strip_non_alpha(data->input);
	size_t cipherlen = strlen(ciphertext);
	if (strcmp(ciphertext, data->input))
		DBG_OUT(
			"Stripped non-alphabetic characters from ciphertext: %s to %s\n",
			data->input, ciphertext)

	char plaintext[cipherlen + 1];
	memset(plaintext, 0, sizeof(plaintext));

	int railc = atoi(data->key);
	if (railc <= 1) {
		printf("Rail count must at least be 2\n");
		exit(EXIT_FAILURE);
	}

	// 2D matrix with railc row and cipherlen col
	char rails[railc][cipherlen]; // Rail data
	int railchc[railc];			  // Rail character count
	memset(railchc, 0, sizeof(railchc));
	memset(rails, 0, sizeof(rails));

	int rail = 0;
	int direction = 1;

	// Count character count per rail
	for (int i = 0; ciphertext[i] != '\0'; i++) {
		railchc[rail]++;

		rail += direction;

		// Direction swapping
		if (rail == 0 || rail == railc - 1)
			direction = -direction;
	}

	if (verbose) {
		for (int i = 0; i < railc; i++) {
			printf("Rail %d character count: %d\n", i, railchc[i]);
		}
	}

	// Reconstruct rails
	int pos = 0;
	int railp[railc];
	memset(railp, 0, sizeof(railp));
	for (int i = 0; i < railc; i++) {
		strncpy(rails[i], ciphertext + pos, railchc[i]);
		rails[i][railchc[i]] = '\0';
		pos += railchc[i];
		DBG_OUT("Reconstructed rail %d: %s\n", i, rails[i])
	}

	// Read plaintext sequentially
	memset(railp, 0, sizeof(railp));

	rail = 0;
	direction = 1;
	for (int i = 0; ciphertext[i] != '\0'; i++) {
		plaintext[i] = rails[rail][railp[rail]++];

		rail += direction;

		// Direction swapping
		if (rail == 0 || rail == railc - 1)
			direction = -direction;
	}
	puts(plaintext);

	free(ciphertext);
}
