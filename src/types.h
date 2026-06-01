#ifndef TYPES_H
#define TYPES_H

typedef struct {
	char *input;
	char *key;
	int verbose;
} cipher_data;

typedef char *(*cipher_fn)(cipher_data *);

typedef struct {
	char *name;
	int require_key;
	int has_crack;
	cipher_fn encode;
	cipher_fn decode;
	cipher_fn crack;
} cipher_entry;

#endif
