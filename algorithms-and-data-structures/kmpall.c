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

int kmpsubst (int *arr, char *S, char *T) {
	int t = 0;
	int h = 0, lt = strlen(T), ls = strlen(S);
	while (h < lt) {
		while (t > 0 && S[t] != T[h])
			t = arr[t - 1];
		if (S[t] == T[h])
			++t;
		if (t == ls)
			printf("%d\n", h - ls + 1);
		++h;
	}
}

int main(int argc, char const *argv[])
{
	int *arr = malloc (strlen(argv[1]) * sizeof(int));
	prefix(arr, argv[1]);
	kmpsubst(arr, argv[1], argv[2]);
	return 0;
}