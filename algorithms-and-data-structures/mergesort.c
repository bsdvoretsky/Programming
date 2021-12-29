#include <stdio.h>
#include <stdlib.h>

void print_arr(size_t n, int a[n]) {
	for (size_t i = 0; i < n; ++i) {
		if (i == n - 1) {
			printf("%d\n", a[i]);
		}
		else {
			printf("%d ", a[i]);
		}
	}
}

void insertsort(int n, int a[n]) {
	int lock, elem;
	for (int i = 1; i < n; ++i) {
		lock = i - 1;
		elem = a[i];
		while (lock >= 0 && (abs(elem) < abs(a[lock]))) {
			a[lock + 1] = a[lock];
			lock--;
		}
		a[lock + 1] = elem;
	}
}

void mergesort(int n, int a[n]) {
	if (n < 5) insertsort(n, a);
	else {
		mergesort((n + 1) / 2, a);
		mergesort(n / 2, a + (n + 1) / 2);
		int b[n], l = 0, r = (n + 1) / 2;
		int i = 0;
		while ((l < (n + 1) / 2) || (r < n)) {
			if ((l < (n + 1) / 2) && (r < n)) {
				if (abs(a[l]) >= abs(a[r])) {
					b[i] = a[r];
					r++;
				}
				else {
					b[i] = a[l];
					l++;
				}
			}
			else if ((l < (n + 1) / 2)) {
				b[i] = a[l];
				l++;
			}
			else {
				b[i] = a[r];
				r++;
			}
			i++;
		}
		for (int k = 0; k < n; ++k) {
			a[k] = b[k];
		}
	}
}

int main(int argc, char **argv)
{
	int n;
	scanf("%d", &n);

	int a[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	mergesort(n, a);
	print_arr(n, a);
	return 0;
}