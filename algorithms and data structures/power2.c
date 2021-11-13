#include <stdio.h>

int main (int argc, char **argv)
{
	int n;
	scanf("%d", &n);
	int nums[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	long m = 1<<n;
	long c = 0;
	long s;

	for (long l = 1; l < m; l++) {
		s = 0;
		for (int i = 0; i < n; i++) {
			if (l & (1<<i)) {
				s += nums[i];
			}
		}
		if ((s & (s - 1)) == 0) {
			c++;
		}
	}

	printf("%ld\n", c);
	return 0;
}