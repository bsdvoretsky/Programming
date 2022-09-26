#include <stdio.h>
#include <string.h>

int main (int argc, char **argv)
{
	int n;
	scanf("%d", &n);

	int a[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	int m;
	scanf("%d", &m);

	char op[4];
	int r, l, i, v, res;

	for (int j = 0; j < m; ++j) {
		scanf("%s", op);
		if (!strcmp(op, "PEAK")) {
			scanf("%d %d", &l, &r);
			if (l == r) {
				printf("1\n");
			}
			else {
				res = 0;
				for (int t = l; t <= r; ++t) {
					if ((t == l && a[t] > a[t + 1]) || (t == r && a[t - 1] < a[t])) {
						res++;
					}
					else if (t != l && t != r && a[t] > a[t - 1] && a[t] > a[t + 1]) {
						res++;
					}
				}
				printf("%d\n", res);
			}
		}
		else if (!strcmp(op, "UPD")) {
			scanf("%d %d", &i, &v);
			a[i] = v;
		}
	}

	return 0;
}