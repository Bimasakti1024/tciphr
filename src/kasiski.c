#include "kasiski.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

kasiski_pattern **find_kasiski_pattern(const char *ciphertext, int gram) {
	// Initiate array of kasiski pattern
	int cipherlen = strlen(ciphertext);
	int kp_count = cipherlen - gram + 1;
	kasiski_pattern **kp = malloc(sizeof(kasiski_pattern *) * (kp_count + 1));

	// Strip non alphabet before finding patterns
	char *cleaned = strip_non_alpha(ciphertext);

	int unique = 0;
	for (int i = 0; i < strlen(cleaned) - gram + 1; i++) {
		// Allocate pattern
		char *pattern = malloc(sizeof(char) * (gram + 1));
		memcpy(pattern, cleaned + i, gram);
		pattern[gram] = '\0';

		int found = 0;

		// Check if pattern already exist
		for (int j = 0; j < unique; j++) {
			if (strcmp(kp[j]->pattern, pattern) == 0) {
				kp[j]->occurences++;
				kp[j]->positions[kp[j]->pos_p++] = i;
				found = 1;
				break;
			}
		}

		// If does not exist, Initiate
		if (!found) {
			// Initiate
			kp[unique] = malloc(sizeof(kasiski_pattern));
			kp[unique]->positions = malloc(sizeof(int) * kp_count);
			kp[unique]->pos_p = 0;

			// Set
			kp[unique]->pattern = strdup(pattern);
			kp[unique]->occurences = 1;
			kp[unique]->positions[kp[unique]->pos_p++] = i;
			unique++;
		}
		free(pattern);
	}

	kp[unique] = NULL;
	free(cleaned);
	return kp;
}

void free_kasisiki_pattern(kasiski_pattern *kp) {
	free(kp->pattern);
	free(kp->positions);
	free(kp);
	return;
}
