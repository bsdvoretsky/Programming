#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prefix(char *a, char *b, int l) {
	for (size_t i = 0; i < l; ++i) {
		if (b[i] != a[i]) return 0;
	}
	return 1;
}

int pword(char *a, char *b) {
	if (strlen(b) == 0) return 1;
	for (size_t i = 0; i < strlen(b); ++i) {
		if (is_prefix(a, b + i, i + 1) && pword(a, b + i + 1)) return 1;
	}
	return 0;
}

int main (int argc, char **argv)
{
	char *s = argv[1], *t = argv[2];
	pword(s, t) ? printf("yes") : printf("no");
	return 0;
}