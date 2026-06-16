#ifndef TYPES_H
#define TYPES_H

typedef struct {
	char strategy[32];
	char *wordlist;
	int gram;
} crack_param;

typedef struct {
	char *input;
	char *key;
	crack_param *crack_parameter;
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
