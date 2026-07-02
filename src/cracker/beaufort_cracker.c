#include "../cipher/ciphers.h"
#include "../types.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int verbose = 0;

char *beaufort_dictionary(cipher_data *data);
char *beaufort_kasiski(cipher_data *data);

char *beaufort_crack(cipher_data *data) {
	verbose = data->verbose;
	char *strategy = data->crack_parameter->strategy;
	int strat_empty = strlen(strategy) == 0;

	if ((strcmp(strategy, "dictionary") == 0) || strat_empty) {
		if (strat_empty) {
			fprintf(stderr, "No strategy given, Defaulting to dictionary\n");
		}
		return beaufort_dictionary(data);
	} else if (strcmp(strategy, "kasiski") == 0) {
		return beaufort_kasiski(data);
	} else {
		fprintf(stderr, "Unknown strategy: %s\n", strategy);
		return NULL;
	}
}

char *beaufort_dictionary(cipher_data *data) {
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
		char *plaintext = beaufort_decode(data);
		if (plaintext)
			printf("Cipherkey %s: %s\n", line, plaintext);
		free(plaintext);
		free(line);
	}

	fclose(wordlist_p);
	return NULL;
}

char *beaufort_kasiski(cipher_data *data) {
	puts("todo");
	return NULL;
}
