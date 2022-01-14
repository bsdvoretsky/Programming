#include <stdio.h>
#include <string.h>
#include <math.h>

int query(int *T, int c, int l, int r, int a, int b) {
  if ((l == a && r == b) || l == r)
    return T[c];
  else {
    int m = (a + b) / 2;
    if (r <= m) {
      return query(T, 2 * c + 1, l, r, a, m);
    }
    else if (l > m) {
      return query(T, 2 * c + 2, l, r, m + 1, b);
    }
    else 
      return fmax(query(T, 2 * c + 1, l, m, a, m), 
                query(T, 2 * c + 2, m + 1, r, m + 1, b));
  }
}

void update(int i, int v, int a, int b, int c, int *T) {
  if (a == b)
    T[c] = v;
  else {
    int m = (a + b) / 2;
    if (i <= m)
      update(i, v, a, m, 2 * c + 1, T);
    else 
      update(i, v, m + 1, b, 2 * c + 2, T);
    T[c] = fmax(T[c * 2 + 1], T[c * 2 + 2]);
  }
}

void build (int *v, int c, int a, int b, int *T) {
  if (a == b) {
    T[c] = v[a];
  }
  else {
    int m = (a + b) / 2;
    build(v, c * 2 + 1, a, m, T);
    build(v, c * 2 + 2, m + 1, b, T);
    T[c] = fmax(T[c * 2 + 1], T[c * 2 + 2]);
  }
}

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	int v[n], i;
	for (i = 0; i < n; ++i) {
		scanf("%d", &v[i]);
	}
	int T[4 * n];
	build(v, 0, 0, n - 1, T);
	char op[4];
	int j, l, r, m, val;
	scanf("%d", &m);
	for (i = 0; i < m; ++i) {
		scanf("%s", op);
		if (!strcmp(op, "MAX")) {
			scanf("%d %d", &l, &r);
			printf("%d\n", query(T, 0, l, r, 0, n - 1));
		}
		else if (!strcmp(op, "UPD")) {
			scanf("%d %d", &j, &val);
			update(j, val, 0, n - 1, 0, T);
		}
	}
	return 0;
}