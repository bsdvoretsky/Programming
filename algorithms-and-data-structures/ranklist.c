#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define VALUE_LEN 10
#define even(v) !(v & 1)

int even(int n) {
	return n % 2 == 0;
}

typedef struct Elem
{
	int k;
	char v[VALUE_LEN];
	struct Elem **next;
	int *span;
} *t_elem;

typedef struct List
{
	t_elem head;
	int n;
	int levels;
	void *buffer;
} *t_list;

t_elem ElemInit(t_list l)
{
	t_elem el = (t_elem)calloc(1, sizeof(struct Elem) + l->levels * sizeof(t_elem) + l->levels * sizeof(int));
	el->next = (t_elem *)(el + 1);
	el->span = (int *)(el->next + l->levels);

	return el;
}

t_list ListInit(int n)
{
	t_list l = (t_list)malloc(sizeof(struct List));
	l->n = n;
	l->levels = (int)log2(n) + 1;
	l->buffer = malloc(l->levels * sizeof(t_elem) + l->levels * sizeof(int));
	l->head = ElemInit(l);

	return l;
}

int Compare(int a, int b)
{
	if (a == b)
		return 0;

	return (a > b) ? 1 : -1;
}

void ListFree(t_list l)
{
	t_elem el_next = l->head;
	t_elem el_curr = NULL;

	while (el_next != NULL)
	{
		el_curr = el_next;
		el_next = el_next->next[0];
		free(el_curr);
	}

	free(l->buffer);
	free(l);
}

t_elem *ElemSkip(t_list l, int k)
{
	t_elem *buff = (t_elem *)l->buffer;
	t_elem el = l->head;

	for (int i = l->levels - 1; i >= 0; --i)
	{
		while (el->next[i] != NULL && Compare(el->next[i]->k, k) == -1)
			el = el->next[i];

		buff[i] = el;
	}

	return buff;
}

t_elem ElemNext(t_elem el)
{
	return el->next[0];
}

t_elem ElemLookup(t_list l, int k)
{
	t_elem *buff = ElemSkip(l, k);
	t_elem el_next = ElemNext(buff[0]);

	return el_next;
}

t_elem ElemInsert(t_list l, int k, char *v)
{
	t_elem el = ElemInit(l);
	el->k = k;
	strcpy(el->v, v);

	int m = l->levels;
	int i = m - 1;
	t_elem *buff = (t_elem *)l->buffer;
	int *distances = (int *)(buff + m);
	t_elem x = l->head;
	int counter;

	while (x->next[i] != NULL && Compare(x->next[i]->k, k) == -1)
		x = x->next[i];

	buff[i] = x;

	for (i = m - 2; i >= 0; --i)
	{
		counter = 0;

		while (x->next[i] != NULL && Compare(x->next[i]->k, k) == -1)
		{
			counter += x->span[i];
			x = x->next[i];
		}

		distances[i + 1] = counter;
		buff[i] = x;
	}

	distances[0] = 0;

	for (i = 1; i < m; ++i)
		distances[i] += distances[i - 1];

	x = el;
	int r = 2 * rand();
	int span_prev;

	for (i = 0; i < l->levels && even(r); ++i)
	{
		x->next[i] = buff[i]->next[i];
		buff[i]->next[i] = x;
		span_prev = buff[i]->span[i];
		buff[i]->span[i] = distances[i] + 1;
		x->span[i] = span_prev - distances[i];
		r /= 2;
	}

	while (i < m)
	{
		++buff[i]->span[i];
		++i;
	}

	return x;
}

void ElemDelete(t_list l, int k)
{
	t_elem *buff = ElemSkip(l, k);
	t_elem el_n = ElemNext(buff[0]);
	int m = l->levels, i = 0;

	for (i = 0; i < m && buff[i]->next[i] == el_n; ++i)
	{
		buff[i]->next[i] = el_n->next[i];
		buff[i]->span[i] += el_n->span[i] - 1;
	}

	while (i < m)
	{
		--buff[i]->span[i];
		++i;
	}

	free(el_n);
}

int ElemRank(t_list l, int k)
{
	int m = l->levels;
	int i = 0;
	t_elem *p = (t_elem *)l->buffer;
	t_elem x = l->head;
	int counter = 0;

	for (i = m - 1; i >= 0; --i)
	{
		while (x->next[i] != NULL && Compare(x->next[i]->k, k) == -1)
		{
			counter += x->span[i];
			x = x->next[i];
		}

		p[i] = x;
	}

	return counter;
}

int main(int argc, char **argv)
{
	int n = 0, i = 0;
	scanf("%d", &n);

	t_list l = ListInit(n);

	char cmd[VALUE_LEN] = { 0 };
	char v[VALUE_LEN] = { 0 };
	int k;

	for (i = 0; i < n; i++)
	{
		scanf("%s %d", cmd, &k);

		if (strcmp(cmd, "INSERT") == 0)
		{
			scanf("%s", v);
			ElemInsert(l, k, v);
		}
		else if (strcmp(cmd, "LOOKUP") == 0) printf("%s\n", ElemLookup(l, k)->v);
		else if (strcmp(cmd, "DELETE") == 0) ElemDelete(l, k);
		else if (strcmp(cmd, "RANK") == 0) printf("%d\n", ElemRank(l, k));
		else return 1;
	}

	ListFree(l);
	return 0;
}