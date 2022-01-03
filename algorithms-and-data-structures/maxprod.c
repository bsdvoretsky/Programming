#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Kadane(long double *array, int len) {

        int l = 0, r = 0, start = 0, i = 0;

	long double sum = 0, maxsum = log2(array[0]);

	while (i < len) {

		sum += log2(array[i]);

		if (sum > maxsum) {

			maxsum = sum;
			l = start;
			r = i;
		}

		i++;

		if (sum < 0) {

			sum = 0;
			start = i;
		}
	}
	printf("%d %d", l, r);

}

int main(int argc, const char *argv[]) {

	int a, b, len;
	long double q;

	scanf("%d", &len);

	long double *array = malloc(sizeof(long double) * len * 2);

	for (int i = 0; i < len; i++) {

		scanf("%d/%d", &a, &b);
		q = (long double)a / (long double)b;
		array[i] = q;
	}

	Kadane(array, len);

	free(array);
	return 0;
}