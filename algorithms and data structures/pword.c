#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prefix(char *a, char *b) {
	for (size_t i = 0; i < strlen(b); ++i) {
		if (b[i] != a[i]) return 0;
	}
	return 1;
}

int pword(char *a, char *b) {
	if (strlen(b) == 0) return 1;
	char *buff = (char *) calloc (sizeof(char), strlen(b));
	for (size_t i = 0; i < strlen(b); ++i) {
		strncpy(buff, b, i + 1);
		if (is_prefix(a, buff) && pword(a, b + i + 1)) {
			free(buff);
			return 1;
		}
		strcpy(buff, "");
	}
	return 0;
}

int main (int argc, char **argv)
{
	char *s = argv[1], *t = argv[2];
	pword(s, t) ? printf("yes") : printf("no");
	return 0;
}