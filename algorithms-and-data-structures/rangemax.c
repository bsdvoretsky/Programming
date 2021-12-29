#include <stdio.h>
#include <string.h>

int main (int argc, char **argv)
{
	int n;
	scanf("%d", &n);

	int a[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	int m, l, r, k, v, t;
	char op[4];
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		if (!strcmp(op, "MAX")) {
			scanf("%d", &l);
			scanf("%d", &r);
			t = -1000000000;
			for (int j = l; j <= r; j++) {
				if (a[j] > t) {
					t = a[j];
				}
			}
			printf("%d\n", t);
		}
		else if (!strcmp(op, "UPD")) {
			scanf("%d", &k);
			scanf("%d", &v);
			a[k] = v;
		}
	}
	return 0;
}