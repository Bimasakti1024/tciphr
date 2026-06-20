#ifndef KASISKI_H
#define KASISKI_H

typedef struct {
	char *pattern;
	int *positions;
	int pos_p;
	int capacity;
	int occurences;
} kasiski_pattern;

kasiski_pattern **find_kasiski_pattern(const char *ciphertext, int gram);
void free_kasisiki_pattern(kasiski_pattern *kp);

#endif
