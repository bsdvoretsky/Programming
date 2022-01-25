#include <stdio.h>
#include <stdlib.h>

struct Elem
{
	struct Elem *prev, *next;
	int v;
};

void Insert(struct Elem *x, struct Elem *y)
{
	struct Elem *z;
	z = x->next;
	x->next = y;
	y->prev = x;
	y->next = z;
	z->prev = y;
}

void Delete(struct Elem *x)
{
	struct Elem *y, *z;
	y = x->prev;
	z = x->next;
	y->next = z;
	z->prev = y;
	x->prev = x->next = NULL;
}

void InSort(struct Elem *t)
{
	struct Elem *j, *loc;
	j = t->next;

	while (j != t)
	{
		loc = j->prev;

		while ((loc != t) && (loc->v > j->v))
			loc = loc->prev;

		Delete(j);
		Insert(loc, j);
		j = j->next;
	}
}

int main()
{
	int n = 0, j = 0;
	scanf("%d", &n);

	struct Elem *t, *p, *g;

	t = (struct Elem *) malloc (sizeof(struct Elem));
	t->next = t->prev = t;

	for (j = 0; j < n; j++)
	{
		p = (struct Elem *) malloc (sizeof(struct Elem));
		scanf("%d", &((*p).v));
		Insert(t, p);
	}

	InSort(t);

	p = t->next;
	while (p != t)
	{
		printf("%d ", p->v);
		g = p;
		p = p->next;
		free(g);
	}
	free(p);
	return 0;
}