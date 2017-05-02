/**
 * The C implementation of string searching algorithm KMP.
 */

#include <stdio.h>
#include <stdlib.h>

void Next(char *pattern, size_t patternlen, int *next) {
	if (patternlen == 0) {
		return;
	}

	next[0] = 0;
	for (int i = 1; i < patternlen; ++i) {
		int j = next[i - 1];
		while (j >= 0 && pattern[j] != pattern[i]) {
			j = next[j] - 1;
		}
		next[i] = j + 1;
	}
}

void KMP(char *str, size_t strlen, char *pattern, int *next, size_t patternlen, int *index, int *substring_number) {
	*substring_number = 0;
	if (strlen == 0 || patternlen == 0 || strlen < patternlen) {
		return;
	}

	int i = 0;
	int j = 0;
	while (i <= strlen - patternlen) {
		while (j < patternlen && pattern[j] == str[i + j]) {
			++j;
		}

		if (j == patternlen) {
			index[*substring_number] = i;
			++*substring_number;
		}

		if (j == 0) {
			++i;
		} else {
			i = i + j - next[j - 1];
			j = next[j - 1];
		}
	}
}

int main() {
	char *str = NULL;
	char *pattern = NULL;
	size_t stringlen = 0;
	size_t patternlen = 0;

	printf("Input charactors string: ");
	if (-1 == (stringlen = getline(&str, &stringlen, stdin))) {
		printf("String read fail!");
		return -1;
	}
	str[stringlen-- - 1] = '\0';

	printf("Input pattern string: ");
	if (-1 == (patternlen = getline(&pattern, &patternlen, stdin))) {
		printf("pattern read fail!");
		return -1;
	}
	pattern[patternlen-- - 1] = '\0';

	printf("Input: \n\tString: %s\n\tpattern: %s\n", str, pattern);

	int next[patternlen];
	Next(pattern, patternlen, next);
	printf("Next: ");
	for (int i = 0; i < patternlen; ++i) {
		printf("%d", next[i]);
	}
	printf("\n");

	int index[stringlen], substring_number;
	KMP(str, stringlen, pattern, next, patternlen, index, &substring_number);

	printf("Result: pattern %d.\nIndex: ", substring_number);
	for (int i = 0; i < substring_number; ++i) {
		printf("\t%d\n", index[i]);
	}

	free(str);
	free(pattern);

	return 0;
}