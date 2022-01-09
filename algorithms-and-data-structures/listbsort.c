#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 1000

typedef struct Elem
{
	struct Elem *next;
	char *word;
} t_elem;

int Compare(t_elem *el)
{
	if (strlen(el->word) == strlen(el->next->word))
		return 0;

	return (strlen(el->word) > strlen(el->next->word)) ? 1 : -1;
}

void Swap(t_elem *first)
{
	t_elem *second = first->next;
	char *tmp = first->word;
	first->word = second->word;
	second->word = tmp;
}

struct Elem *bsort(struct Elem *list)
{
	t_elem *i, *n = list->next;
	int swap = 0;

	while (n->next != NULL)
		n = n->next;

	do
	{
		swap = 0;

		for (i = list->next; i != n; i = i->next)
			if (Compare(i) == 1)
			{
				Swap(i);
				swap = 1;
			}

		n = i;
	} while (swap == 1);

	return list;
}

t_elem* ElemInit(char *w)
{
	int len = strlen(w);

	if (len && w[len - 1] == '\n')
		w[--len] = '\0';

	t_elem *el;
	el = (t_elem*)malloc(sizeof(t_elem));
	el->next = NULL;
	el->word = (char*)calloc(len + 1, sizeof(char));
	strcpy(el->word, w);

	return el;
}

int main()
{
	char src[STR_LEN] = { 0 };
	fgets(src, STR_LEN - 1, stdin);

	t_elem *head, *el1, *el2;
	head = el1 = el2 = NULL;
	head = ElemInit("");
	el1 = head;

	char sep[2] = { ' ' };
	char *istr = strtok(src, sep);
	while (istr != NULL)
	{
		el2 = ElemInit(istr);
		el1->next = el2;
		el1 = el2;
		istr = strtok(NULL, sep);
	}

	bsort(head);

	el1 = head->next;
	while (el1 != NULL)
	{
		printf("%s ", el1->word);
		el2 = el1->next;

		el1->next = NULL;
		free(el1->word);
		free(el1);

		el1 = el2;
	}
	head->next = NULL;
	free(head->word);
	free(head);
	return 0;
}