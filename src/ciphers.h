#ifndef CIPHERS_H
#define CIPHERS_H
#include "types.h"

extern cipher_entry cipher_table[];

// DECLARE_CIPHER(name, require_key, has_crack)
#define CIPHER_LIST                                                            \
	X(caesar, 1, 1)                                                            \
	X(rot13, 0, 0)                                                             \
	X(atbash, 0, 0)                                                            \
	X(autokey, 1, 0)                                                           \
	X(vigenere, 1, 1)                                                          \
	X(beaufort, 1, 0)                                                          \
	X(railfence, 1, 1)

#define DECLARE_CRACK_1(name) char *name##_crack(cipher_data *data);
#define DECLARE_CRACK_0(name)

#define EVAL_CRACK(macro, name) macro(name)
#define DECLARE_CRACK_CHOOSE(name, has_crack)                                  \
	EVAL_CRACK(DECLARE_CRACK_##has_crack, name)

#define DECLARE_CIPHER(name)                                                   \
	char *name##_encode(cipher_data *data);                                    \
	char *name##_decode(cipher_data *data);

#define X(name, require_key, has_crack)                                        \
	DECLARE_CRACK_CHOOSE(name, has_crack) DECLARE_CIPHER(name)
CIPHER_LIST
#undef X
#undef DECLARE_CRACK_1
#undef DECLARE_CRACK_0
#undef EVAL_CRACK
#undef DECLARE_CRACK_CHOOSE

cipher_entry *find_cipher(const char *name);
void list_ciphers();

#endif // CIPHERS_H