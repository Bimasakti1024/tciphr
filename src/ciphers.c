#include "ciphers.h"
#include <stdio.h>
#include <string.h>

#define DEFINE_CRACK_PTR_1(name) name##_crack
#define DEFINE_CRACK_PTR_0(name) NULL
#define EVAL_CRACK_PTR(macro, name) macro(name)

#define X(name, require_key, has_crack)                                        \
	{#name,			require_key,                                               \
	 has_crack,		name##_encode,                                             \
	 name##_decode, EVAL_CRACK_PTR(DEFINE_CRACK_PTR_##has_crack, name)},

cipher_entry cipher_table[] = {CIPHER_LIST{NULL, 0, 0, NULL, NULL, NULL}};
#undef X
#undef DEFINE_CRACK_PTR_1
#undef DEFINE_CRACK_PTR_0
#undef EVAL_CRACK_PTR

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
