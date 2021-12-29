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

unsigned long max_fib(unsigned long x) {
	unsigned long i = 0;
	unsigned long j = 1;
	unsigned long k = 1;
	unsigned long t;
	if (x == 1) {
		return 0;
	}
	while (k < x) {
		t = i;
		i = j;
		j = j + t;
		if ((i + j) >= x) {
			return j;
		}
		k = i + j;
	}
	return k;
}

int a[10] = {4, 1, 10, 5, 7, 3, 2, 6, 8, 9};

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

void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
	unsigned long d = max_fib(nel);
	unsigned long i = d;
	long loc;
	while (d >= 1) 
	{
		while (i < nel) 
		{
			loc = i - d;
			while ((loc >= 0) && (compare(i, loc) == -1)) 
			{
				loc = loc - d;
			}
			loc = loc + d;
			for (unsigned long j = 0; j < (i - loc); j++) {
				swap(i - j - 1, i - j);
			}
			i++;
		}
		d = max_fib(d);
		i = d;
	}
}

int main (int argc, char **argv)
{
	shellsort(10, compare, swap);
	print_arr(a, 10);
	return 0;
}