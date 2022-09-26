#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return a<b ? a : b;
}

int max(int a, int b) {
	return a>b ? a : b;
}

void make_bin_str(char *str, int *buff) {
	int l = strlen(str) + 1;
	for (int i = l - 1; i >= 0; --i) {
		for (int j = 7; j >= 0; --j) {
			buff[(l - 1 - i) * 8 + j] = (int) str[i] >> (7 - j) & 1;
		}
	}
}

int strdiff(char *a, char *b)
{ 
	int l_a = strlen(a) + 1,
		l_b = strlen(b) + 1;
	int *buff_a = (int*) calloc (l_a * 8, sizeof(int));
	int *buff_b = (int*) calloc (l_b * 8, sizeof(int));
	make_bin_str(a, buff_a);
	make_bin_str(b, buff_b); 
	for (int i = 0; i < l_a * 8; ++i) {
		printf("%d", buff_a[i]);
		if (i % 8 == 7) {
			printf("\n");
		}
	}
	printf("\n");
	for (int i = 0; i < l_b * 8; ++i) {
		printf("%d", buff_b[i]);
		if (i % 8 == 7) {
			printf("\n");
		}
	}
	for (int i = 0; i < min(l_b, l_a) * 8; ++i) {
		if (buff_a[l_a * 8 - i - 1] != buff_b[l_b * 8 - i - 1]) {
			free(buff_a);
			free(buff_b);
			return (i);
		}
	}
	free(buff_a);
	free(buff_b);
	return -1;
}

int main(int argc, char const *argv[])
{
	char *a = "The quick brown fox jumps over the lazy dog",
		 *b = "The quick brown fox jumps over the lazy do";
	printf("%d\n", strdiff(a, b));
	return 0;
}