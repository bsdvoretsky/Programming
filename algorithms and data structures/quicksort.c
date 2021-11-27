#include <stdio.h>

void selection_sort(int *a, int n) {
	int m = a[0];
	int c = 0, t;
	for (int i = 0; i < n; ++i) {
		if (a[i] < m) {
			m = a[i];
			c = i;
		}
	}
	t = a[0];
	a[0] = m;
	a[c] = t;
	if (n > 1)
		selection_sort(a + 1, n - 1);
}

void quicksort(int *a, int n, int m) {
	if (n < m) {
		selection_sort(a, n);
	}
	else {
		if (n == 2) {
			if (a[0] > a[1]) {
				int t = a[0];
				a[0] = a[1];
				a[1] = t;
			}
		}
		else if (n > 2) {
			int mid = n / 2;
			int b[n];
			int k = 0, p;
			for (int i = 0; i < n; ++i) {
				if (a[i] < a[mid]) {
					b[k] = a[i];
					k++;
				}
			}
			p = k;
			b[k] = a[mid];
			k++;
			for (int i = 0; i < n; ++i) {
				if (a[i] > a[mid]) {
					b[k] = a[i];
					k++;
				}
			}
			for (int i = 0; i < n; i++) {
				a[i] = b[i];
			}
			quicksort(a, p, m);
			quicksort(a + p + 1, n - p - 1, m);
		}
	}
}

int main(int argc, char **argv)
{
	int n, m;
	scanf("%d %d", &n, &m);
	int a[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	quicksort(a, n, m);
	
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}