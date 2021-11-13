#include <stdio.h>

void print_arr(int *arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d\n", arr[i]);
		}
		else {
			printf("%d ", arr[i]);
		}
	}
}

int a[10] = {5, 4, 2, 1, 3, 10, 7, 9, 6, 8};

void swap(unsigned long i, unsigned long j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

int compare(unsigned long i, unsigned long j) {
	if (a[i] < a[j]) return -1;
	else if (a[i] == a[j]) return 0;
	return 1;
}

void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
	int fl = 0;

	for (unsigned long i = 0; i < nel; i++) {
		if (i % 2 == 0) {
			for (unsigned long j = 0; j < nel - 1; j++) {
				if (compare(j, j + 1) == 1) {
					swap(j, j + 1);
					fl = 1;
				}
			}
			if (fl == 0) {
				break;
			}
		}
		else {
			for (unsigned long j = nel - 1; j > 0; j--) {
				if (compare(j - 1, j) == 1) {
					swap(j - 1, j);
					fl = 1;
				}
			}
			if (fl == 0) {
				break;
			}
		}
		fl = 0;
	}
}

int main (int argc, char **argv)
{
	bubblesort(10, compare, swap);
	print_arr(a, 10);
	return 0;
}