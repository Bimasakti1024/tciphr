#include "../cipher/ciphers.h"
#include "../types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *caesar_crack(cipher_data *data) {
	for (int i = 0; i <= 25; i++) {
		char *output = caesar_decode(data);
		printf("Shift %2d: %-s\n", i, output);
		free(output);
	}
	return NULL;
}
