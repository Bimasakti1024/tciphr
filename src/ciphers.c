#include "ciphers.h"
#include <stdio.h>
#include <string.h>

#define X(name, require_key) {#name, name##_encode, name##_decode, require_key},
cipher_entry cipher_table[] = {CIPHER_LIST{NULL, NULL, NULL, 0}};
#undef X

cipher_entry *find_cipher(const char *name) {
	if (!name)
		return NULL;
	for (int i = 0; cipher_table[i].name != NULL; i++) {
		if (strcmp(cipher_table[i].name, name) == 0)
			return &cipher_table[i];
	}
	return NULL;
}

void list_ciphers() {
	const char *no_yes[] = {"no", "yes"};
	printf("%-12s%s\n", "cipher", "Require key");
	for (int i = 0; cipher_table[i].name != NULL; i++) {
		printf("%-12s%s\n", cipher_table[i].name,
			   no_yes[cipher_table[i].require_key]);
	}
}
