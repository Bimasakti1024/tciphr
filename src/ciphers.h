#ifndef CIPHERS_H
#define CIPHERS_H
#include "types.h"

extern cipher_entry cipher_table[];

// X(name, require_key)
#define CIPHER_LIST                                                            \
	X(caesar, 1)                                                               \
	X(rot13, 0)                                                                \
	X(atbash, 0)                                                               \
	X(vigenere, 1)                                                             \
	X(beaufort, 1)                                                             \
	X(railfence, 1)

#define DECLARE_CIPHER(name)                                                   \
	void name##_encode(cipher_data *data);                                     \
	void name##_decode(cipher_data *data);

#define X(name, require_key) DECLARE_CIPHER(name)
CIPHER_LIST
#undef X

cipher_entry *find_cipher(const char *name);
void list_ciphers();

#endif // CIPHERS_H