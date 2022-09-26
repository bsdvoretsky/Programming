#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Elem
{
	int k, v;
	struct Elem *next;
} t_elem;

t_elem* ElemInit()
{
	t_elem *elem = (t_elem*)malloc(sizeof(struct Elem));
	elem->k = 0;
	elem->v = 0;
	elem->next = NULL;

	return elem;
}

t_elem** TableInit(size_t m)
{
	t_elem **t = (t_elem**)malloc(m * sizeof(t_elem*));

	for (size_t i = 0; i < m; i++)
		t[i] = ElemInit();

	return t;
}

int ElemFind(t_elem **t, size_t m, size_t k)
{
	int ret = 0;
	t_elem *elem = t[k % m];

	while (elem && elem->k != k)
		elem = elem->next;

	if (elem)
		ret = elem->v;

	return ret;
}

void ElemInsert(t_elem **t, size_t m, size_t k, long v)
{
	t_elem *elem = ElemInit();
	elem->k = k;
	elem->v = v;
	elem->next = t[k % m];
	t[k % m] = elem;
}

int main(int argc, char const *argv[])
{
	int n, t, q, m = 100000;
	scanf("%d", &n);
	t_elem **table = TableInit(m);
	unsigned int res = 0;
	long long s = 0;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &t);
		s ^= t;
		q = ElemFind(table, m, s);
		if (!q) {
			ElemInsert(table, m, s, 1);
		}
		else {
			res += q;
			ElemInsert(table, m, s, q + 1);
		}
		if (s == 0) {
			++res;
		}
	}

	printf("%u", res);

	t_elem *el_c = 0;
	t_elem *el_t = 0;

	for (int i = 0; i < m; i++)
	{
		el_c = table[i];

		while (el_c)
		{
			el_t = el_c->next;
			free(el_c);
			el_c = el_t;
		}
	}
	free(table);
	return 0;
}