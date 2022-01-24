#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Pair {
	int key;
	int value;
};

int main(int argc, char const *argv[])
{
	int n, t, q = -1;
	scanf("%d", &n);
	struct Pair *arr = calloc (100000, sizeof(struct Pair));
	int k = 0;
	unsigned int res = 0;
	long long s = 0;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &t);
		s ^= t;
		for (int j = 0; j < k; ++j) {
			if (arr[j].key == s) {
				q = arr[j].value;
				++arr[j].value;
				break;
			}
		}
		if (q == -1 || k == 0) {
			arr[k].key = s;
			arr[k].value = 1;
			++k;
		}
		else {
			res += q;
			q = -1;
		}
		if (s == 0) {
			++res;
		}
	}

	printf("%u", res);
	free(arr);
	return 0;
}