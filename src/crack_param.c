#include "crack_param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_KV(k, s) if (strcmp(k, s) == 0)
#define EMAP_KV(k, s) else MAP_KV(k, s)

void parse_crack_param(crack_param *crack_parameter, char *str) {
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	strncpy(buffer, str, sizeof(buffer) - 1);

	char *token = strtok(buffer, ",");
	while (token) {
		char *eq = strchr(token, '=');

		if (eq) {
			*eq = '\0';
			char *key = token;
			char *val = eq + 1;

			if (*val == '\0') {
				continue;
			}

			printf("%s=%s\n", key, val);

			MAP_KV(key, "strategy") {
				strncpy(crack_parameter->strategy, val,
						sizeof(crack_parameter->strategy) - 1);
				crack_parameter
					->strategy[sizeof(crack_parameter->strategy) - 1] = '\0';
			}
			EMAP_KV(key, "wordlist") {
				crack_parameter->wordlist = strdup(val);
			}
			EMAP_KV(key, "gram") { crack_parameter->gram = atoi(val); }
		}
		token = strtok(NULL, ",");
	}

	return;
}
