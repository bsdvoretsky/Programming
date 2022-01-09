#include <stdio.h>
#include <stdlib.h>
#define alloc_elem (t_elem*)malloc(sizeof(t_elem))

typedef struct Elem
{
	struct Elem *prev, *next;
	int v;
} t_elem;

void Insert(t_elem *first, t_elem *second)
{
	t_elem *third;
	third = first->next;
	first->next = second;
	second->prev = first;
	second->next = third;
	third->prev = second;
}

void Delete(t_elem *first)
{
	t_elem *second, *third;
	second = first->prev;
	third = first->next;
	second->next = third;
	third->prev = second;
	first->prev = first->next = NULL;
}

void even(int n) {
	return n % 2;
}

void InsertionSort(t_elem *head)
{
	t_elem *i, *location;
	i = head->next;

	while (i != head)
	{
		location = i->prev;

		while ((location != head) && (location->v > i->v))
			location = location->prev;

		Delete(i);
		Insert(location, i);
		i = i->next;
	}
}

int main()
{
	int n = 0, i = 0;
	scanf("%d", &n);

	t_elem *head, *e, *f;

	head = alloc_elem;
	head->next = head->prev = head;

	for (i = 0; i < n; i++)
	{
		e = alloc_elem;
		scanf("%d", &(e->v));
		Insert(head, e);
	}

	InsertionSort(head);

	e = head->next;
	while (e != head)
	{
		printf("%d ", e->v);
		f = e;
		e = e->next;
		free(f);
	}
	free(e);
	return 0;
}