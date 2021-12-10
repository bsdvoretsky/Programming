#include <stdio.h>

void selection_sort(int *a, int l, int r) {
	int m, x;
	for (int i = l; i < r - 1; ++i) {
		m = a[i];
		x = i;
		for (int j = i + 1; j <= r; ++j) {
			if (a[j] < m) {
				m = a[j];
				x = j;
			}
		}
		a[x] = a[i];
		a[i] = m;
	}
}

void quicksort(int *a, int m, int l, int r) {
	if ((r - l + 1) < m) {
		selection_sort(a, l, r);
	}
	else {
		int mid = a[(l + r) / 2];
		int i = l;
		int j = r;
		int t;
		while (i <= j) {
			while (a[i] < mid) {
				i++;
			}
			while (a[j] > mid) {
				j--;
			}
			if (i <= j) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
				i++;
				j--;
			}
		}
		if (r > i) {
			quicksort(a, m, i, r);
		}
		if (l < j) {
			quicksort(a, m, l, j);
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
	quicksort(a, m, 0, n - 1);
	
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}