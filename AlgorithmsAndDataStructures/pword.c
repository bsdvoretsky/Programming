#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix(int *arr, char *S) {
	int q = 0;
	arr[0] = q;
	int j = 1, l = strlen(S);
	while (j < l) {
		while (q > 0 && S[q] != S[j])
			q = arr[q - 1];
		if (S[q] == S[j])
			++q;
		arr[j] = q;
		++j;
	}
}

int pword(char *S, char *T) {
	int i = 0, lt = strlen(T), ls = strlen(S);
	int n = lt + ls + 2;
	char *concat = calloc (n, sizeof(char));
	sprintf(concat, "%s%c%s", S, '#', T);
	n = n - 1;
	int *arr = calloc (n, sizeof(int));
	prefix(arr, concat);

	for (i = ls + 1; i < n; ++i) {
		if (arr[i] == 0) {
			free(concat);
			free(arr);
			return 0;
		}
	}

	free(concat);
	free(arr);
	return 1;
}

int main(int argc, char const *argv[])
{
	printf("%s\n", pword(argv[1], argv[2]) ? "yes" : "no");
	return 0;
}