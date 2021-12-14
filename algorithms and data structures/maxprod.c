#include <stdio.h>

int main(int argc, char **argv)
{
	int n;
	scanf("%d", &n);
	int gap = 1, a, b, tl, l = 0, r = 0;
	float max = -1, temp = 1;
	for (int i = 0; i < n; ++i) {
		scanf("%d/%d", &a, &b);
		if (!gap) {
			if (a >= b) {
				temp *= (a / b);
			}
			else {
				if (temp > max) {
					max = temp;
					l = tl;
					r = i - 1;
					temp = 1;
				}
				gap = 1;
			}
		}
		else {
			if (a >= b) {
				temp = a / b;
				tl = i;
				gap = 0;
			}
		}
	}
	if (temp > max) {
		max = temp;
		l = tl;
		r = n - 1;
	}
	printf("%d %d\n", l, r);
	return 0;
}