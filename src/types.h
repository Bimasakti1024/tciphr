#ifndef TYPES_H
#define TYPES_H

typedef struct {
	char *input;
	char *key;
	int verbose;
} cipher_data;

typedef void (*cipher_fn)(cipher_data *);

typedef struct {
	char *name;
	cipher_fn encode;
	cipher_fn decode;
	int require_key;
} cipher_entry;

#endif
