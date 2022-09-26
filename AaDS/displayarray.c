#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(void)
{
	size_t n = 0, m = 0, i = 0, k = 0;
	int v = 0;
	scanf("%u %u", &n, &m);

	char cmd[7] = { 0 };
	t_elem **table = TableInit(m);

	int *result = (int*)calloc(n, sizeof(int));
	size_t ri = 0;

	for (i = 0; i < n; i++)
	{
		scanf("%s %u", cmd, &k);

		if (strcmp(cmd, "AT") == 0)
			result[ri++] = ElemFind(table, m, k);
		else
		{
			scanf("%d", &v);
			ElemInsert(table, m, k, v);
		}
	}

	for (i = 0; i < ri; i++)
		printf("%d\n", result[i]);

	t_elem *el_c = 0;
	t_elem *el_t = 0;

	for (i = 0; i < m; i++)
	{
		el_c = table[i];

		while (el_c)
		{
			el_t = el_c->next;
			free(el_c);
			el_c = el_t;
		}
	}

	free(result);
	free(table);
	table = NULL;
	return 0;
}