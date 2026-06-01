#include "ciphers.h"
#include "types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void show_help(const char *program_name);

int main(int argc, char **argv) {
	// Read flag arguments
	int opt;
	char *key = NULL;
	int verbose = 0;
	int decode = 0;
	int crack = 0;
	char *cipher;
	char *buffer;

	while ((opt = getopt(argc, argv, "c:k:dvlCh")) != -1) {
		switch (opt) {
		case 'c': {
			cipher = strdup(optarg);
			for (int i = 0; optarg[i] != '\0'; i++) {
				cipher[i] = tolower(optarg[i]);
			}
			break;
		}
		case 'k': {
			key = optarg;
			break;
		}
		case 'd': {
			decode = 1;
			break;
		}
		case 'v': {
			verbose = 1;
			break;
		}
		case 'l': {
			list_ciphers();
			exit(EXIT_FAILURE);
		}
		case 'C': {
			crack = 1;
			break;
		}
		case 'h': {
			show_help(argv[0]);
			exit(EXIT_SUCCESS);
		}
		case '?': {
			show_help(argv[0]);
			exit(EXIT_FAILURE);
		}
		}
	}

	// Read stdin with dynamic buffer
	// Initial capacity of 1024
	size_t capacity = 1024;
	size_t len = 0;
	char *input = malloc(capacity);
	if (!input)
		exit(EXIT_FAILURE);

	// Iterate each stdin and realloc
	int c;
	while ((c = getchar()) != EOF) {
		if (len + 1 >= capacity) {
			capacity = (size_t)(capacity * 1.5);
			char *tmp = realloc(input, capacity);
			if (!tmp) {
				free(input);
				exit(EXIT_FAILURE);
			}
			input = tmp;
		}
		input[len++] = (char)c;
	}

	// Strip newline
	if (len > 0 && input[len - 1] == '\n')
		input[--len] = '\0';

	// Null Terminator
	input[len] = '\0';

	cipher_data data = {
		.input = input,
		.key = key,
		.verbose = verbose,
	};

	// Check for stdin
	if (data.input) {
		// Find and execute cipher
		cipher_entry *entry = find_cipher(cipher);

		if (entry) {
			if ((entry->require_key && !data.key) && !crack) {
				printf("Key is required\n");
			} else {
				if (decode) {
					buffer = entry->decode(&data);
				} else if (crack) {
					if (entry->crack) {
						buffer = entry->crack(&data);
					} else {
						printf("Cracking for %s is not supported\n", cipher);
					}
				} else
					buffer = entry->encode(&data);
			}
		} else if (!entry) {
			printf("Cipher %s not found\n", cipher);
		}
	} else {
		if (decode || crack)
			printf("No ciphertext were given\n");
		else
			printf("No plaintext were given\n");
	}

	if (buffer) {
		puts(buffer);
		free(buffer);
	}

	free(cipher);
	free(input);
	return 0;
}

void show_help(const char *program_name) {
	printf("Usage: %s -c <cipher> [-k <key>] [-d] [-C] [-v] [-l] [-h]\n\n",
		   program_name);
	printf("Options:\n");
	printf("  -c <cipher>   Specify the cipher algorithm to use\n");
	printf("  -k <key>      Provide the key for encryption or decryption\n");
	printf("  -d            Decode ciphertext\n");
	printf("  -C            Attempt to crack a ciphertext\n");
	printf("  -v            Enable verbose debugging output\n");
	printf("  -l            List all available ciphers supported by tciphr\n");
	printf("  -h            Display this help menu and exit\n");
}
