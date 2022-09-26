#include <stdio.h>
#include <string.h>

#define ALPHABET 26

int main(int argc, char **argv)
{
	char *s = argv[1], *t = argv[2];
	int expand_stop_symbols[strlen(s)][ALPHABET];
	for (int i = 0; i < strlen(s); ++i) {
		for (int j = 0; j < ALPHABET; ++j) {
			expand_stop_symbols[i][j] = -1;
			for (int k = i - 1; k >= 0; --k) {
				if ((s[k] == (char) (j + 97)) && expand_stop_symbols[i][j] == -1) {
					expand_stop_symbols[i][j] = k;
				}
			}
		}
	}

	int k = 0, last = strlen(s) - 1, p;
	int fl = 0;
	while (k < strlen(t) - last) {
		p = last;
		while ((p >= 0) && (t[k + p] == s[p])) p--;
		if (p == -1) {
			printf("%d\n", k);
			fl = 1;
			k++;
		}
		else {
			k += p - expand_stop_symbols[p][(int) t[k + p] - 97];
		}
	}
	if (fl == 0) printf("%lu", strlen(t));
	return 0;
}