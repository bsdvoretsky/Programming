#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t prefix(char *str, size_t i, size_t k, size_t *prefix_arr) {
	if (str[i] == str[k]) return k + 1;
	if (k == 0) return 0;
	prefix(str, i, prefix_arr[k - 1], prefix_arr);
}

void entry(char *a, size_t l) {
	size_t prefix_arr[strlen(a)];
	prefix_arr[0] = 0;
	for (size_t i = 1; i < strlen(a); ++i) {
		prefix_arr[i] = prefix(a, i, prefix_arr[i - 1], prefix_arr);
		if (i > l && prefix_arr[i] == l) printf("%lu\n", i - 2 * l);
	}
}


int main (int argc, char **argv)
{
	char *s = argv[1], *t = argv[2];
	char *a = (char *) malloc (strlen(s) + strlen(t) + 2);
	strcpy(a, s);
	strcpy(a + strlen(s), "#");
	strcpy(a + strlen(s) + 1, t);
	strcpy(a + strlen(s) + 1 + strlen(t), "\0");
	entry(a, strlen(s));
	free(a);
	return 0;
}