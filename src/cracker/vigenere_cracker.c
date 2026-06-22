#include "../cipher/ciphers.h"
#include "../kasiski.h"
#include "../types.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

char *vigenere_dictionary(cipher_data *data);
char *vigenere_kasiski(cipher_data *data);

char *vigenere_crack(cipher_data *data) {
	verbose = data->verbose;
	char *strategy = data->crack_parameter->strategy;
	int strat_empty = strlen(strategy) == 0;

	if ((strcmp(strategy, "dictionary") == 0) || strat_empty) {
		if (strat_empty) {
			fprintf(stderr, "No strategy given, Defaulting to dictionary\n");
		}
		return vigenere_dictionary(data);
	} else if (strcmp(strategy, "kasiski") == 0) {
		return vigenere_kasiski(data);
	} else {
		fprintf(stderr, "Unknown strategy: %s\n", strategy);
		return NULL;
	}
}

char *vigenere_dictionary(cipher_data *data) {
	char *wordlist = data->crack_parameter->wordlist;
	if (!wordlist) {
		fprintf(stderr, "Wordlist path not provided\n");
		return NULL;
	}
	FILE *wordlist_p = fopen(wordlist, "r");
	if (!wordlist_p) {
		fprintf(stderr, "Failed to open file\n");
		return NULL;
	}

	char *line;
	while ((line = readline_file(wordlist_p)) != NULL) {
		line[strlen(line)] = '\0';
		data->key = line;
		char *plaintext = vigenere_decode(data);
		if (plaintext)
			printf("Cipherkey %s: %s\n", line, plaintext);
		free(plaintext);
		free(line);
	}

	fclose(wordlist_p);
	return NULL;
}

char *vigenere_kasiski(cipher_data *data) {
	kasiski_pattern **kp =
		find_kasiski_pattern(data->input, data->crack_parameter->gram);

	int result = 0;
	for (int i = 0; kp[i] != NULL; i++) {
		if (kp[i]->occurences < 2) {
			free_kasiski_pattern(kp[i]);
			continue;
		}

		DBG_OUT("pattern: %s occurence: %d position: ", kp[i]->pattern,
				kp[i]->occurences);

		for (int j = 0; j < kp[i]->occurences; j++)
			DBG_OUT("%d ", kp[i]->positions[j]);

		DBG_OUT("spacing: ");
		for (int j = 0; j < kp[i]->occurences - 1; j++) {
			DBG_OUT("%d ", kp[i]->spacings[j]);
			result = gcd(result, kp[i]->spacings[j]);
		}

		DBG_OUT("\n");
		free_kasiski_pattern(kp[i]);
	}

	printf("Predicted key length: %d\n", result);
	free(kp);
	return NULL;
}
