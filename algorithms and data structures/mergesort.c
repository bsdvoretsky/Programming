#include <stdio.h>
#include <stdlib.h>

void print_arr(int *a, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		if (i == n - 1) {
			printf("%d\n", a[i]);
		}
		else {
			printf("%d ", a[i]);
		}
	}
}

int *insert_abs_sort(int *a, int b, int e) {
	int i = 1, loc, elem;
	int *t = malloc((e - b + 1) * sizeof(int));
	for (int j = b; j <= e; j++) {
		t[j - b] = a[j];
	}
	while (i < (e - b + 1)) {
		loc = i - 1;
		elem = t[i];
		while (loc >= 0 && abs(elem) < abs(t[loc])) {
			t[loc + 1] = t[loc];
			loc--;
		}
		t[loc + 1] = elem;
		i++;
	}
	return t;
}

int *merge_abs_sort(int *up, int *down, int b, int e, int fl) {
	int m;
	int *c, *d, *t;
	if ((e - b + 1) < 5 && fl) {
		return	insert_abs_sort(up, b, e);
	}
	else {
		if (e == b) {
			down[e] = up[e];
			return down;
		}
		m = (e + b) / 2;
		c = merge_abs_sort(up, down, b, m, 0);
		d = merge_abs_sort(up, down, m + 1, e, 0);

		t = c == up ? down : up;

	    int b_cur = b, e_cur = m + 1;
	    for (int i = b; i <= e; i++)
	    {
	        if (b_cur <= m && e_cur <= e)
	        {
	            if (abs(c[b_cur]) < abs(d[e_cur]))
	            {
	                t[i] = c[b_cur];
	                b_cur++;
	            }
	            else
	            {
	                t[i] = d[e_cur];
	                e_cur++;
	            }
	        }
	        else if (b_cur <= m)
	        {
	            t[i] = c[b_cur];
	            b_cur++;
	        }
	        else
	        {
	            t[i] = d[e_cur];
	            e_cur++;
	        }
	    }
	    return t;
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

	int *b = malloc(n * sizeof(int));
	b = merge_abs_sort(a, b, 0, n - 1, 1);
	print_arr(b, n);
	return 0;
}