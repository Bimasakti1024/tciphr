#include "../cipher/ciphers.h"
#include "../types.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *beaufort_crack(cipher_data *data) {
	char *wordlist = data->crack_parameter->wordlist;
	if (!wordlist) {
		printf("Wordlist path not provided\n");
		return NULL;
	}
	FILE *wordlist_p = fopen(wordlist, "r");
	if (!wordlist_p) {
		printf("Failed to open file\n");
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
