#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 10003

struct Elem {
    struct Elem *following;
    char *w;
};

void swap(char **a, char **b) {
	char *t = *a;
	*a = *b;
	*b = t;
}

size_t compare(char *a, char *b) {
	return (strlen(a) > strlen(b));
}

struct Elem *bsort(struct Elem *list)
{
	if (list == NULL || (*list).following == NULL)
		return list;

    int fl = 1;

    struct Elem *c, *n;

    while (fl == 1)
    {
    	fl = 0;

    	c = list;
    	n = (*list).following;

    	while (n != NULL)
    	{
    		if (compare((*c).w, (*n).w))
    		{
    			fl = 1;
    			swap(&((*c).w), &((*n).w));
    		}

    		c = (*c).following;
    		n = (*n).following;

    	}
    }

    return list;
}

struct Elem *ActiveElem(char **w)
{
	size_t len = strlen(*w);

	if (len && (*w)[len - 1] == '\n')
		(*w)[--len] = '\0';

	struct Elem *e = (struct Elem *) malloc (sizeof(struct Elem));
	(*e).following = NULL;
	(*e).w = *w;

	return e;
} 

int main()
{
	char *src = (char *) malloc (BSIZE * sizeof(char));
	char *fsrc = src;

	fgets(src, BSIZE, stdin);

	struct Elem *l, *c, *n;
	l = c = n = NULL;

	char *idler = " ";
	char *w = strtok(src, idler);

	l = ActiveElem(&w);
	c = l;

	w = strtok(NULL, idler);

	while (w != NULL)
	{
		n = ActiveElem(&w);
		(*c).following = n;
		c = n;
		
		w = strtok(NULL, idler);
	}

	bsort(l);

	c = l;
	while (c != NULL)
	{
		printf("%s\n", (*c).w);
		n = (*c).following;

		free(c);

		c = n;
	}

	free(fsrc);

	return 0;
}