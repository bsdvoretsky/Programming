#include <stdio.h>
#include <stdlib.h>

struct Pair
{
	int index;
	int value;
};

struct Queue
{
	struct Pair **heap;
	int cap;
	int count;
} q;


void Heapify(int i, int n)
{
	int left, right, j;
	struct Pair* swapper;
	for(;;)
	{
		left = 2 * i + 1;
		right = left + 1;
		j = i;

		if (left < n && q.heap[i]->value < q.heap[left]->value)
			i = left;
		if (right < n && q.heap[i]->value < q.heap[right]->value)
			i = right;
		if (i == j)
			break;

		swapper = q.heap[i];
		q.heap[i] = q.heap[j];
		q.heap[j] = swapper;

		q.heap[i]->index = i;
		q.heap[j]->index = j;
	}
}

void InitPriorityQueue(int k)
{
	q.heap = (struct Pair **) malloc (k * sizeof(struct Pair));
	q.cap = k;
	q.count = 0;
}

struct Pair* Minimum()
{
	if (q.count == 0)
	{
		printf("error: queue is empty\n");
		exit(1);
	}

	return q.heap[0];
}

int QueueEmpty()
{
	return (q.count == 0);
}

void Insert(struct Pair *ptr)
{
	int i = q.count;

	if (i == q.cap)
	{
		printf("error: overflow\n");
		exit(1);
	}

	q.count = i + 1;
	q.heap[i] = ptr;
	struct Pair *swapper;
	while (i > 0 && q.heap[ (i - 1) / 2 ]->value < q.heap[i]->value)
	{
		swapper = q.heap[ (i - 1) / 2 ];
		q.heap[ (i - 1) / 2 ] = q.heap[i];
		q.heap[i] = swapper;

		q.heap[i]->index = i;
		i = (i - 1) / 2;
	}

	q.heap[i]->index = i;
}

struct Pair* ExtractMin()
{
	if (q.count == 0)
	{
		printf("error: queue is empty\n");
		exit(1);
	}

	struct Pair *ptr = q.heap[0];
	--(q.count);

	if (q.count > 0)
	{
		q.heap[0] = q.heap[q.count];
		q.heap[0]->index = 0;
		Heapify(0, q.count);
	}

	return ptr;
}

void QueueProcess(int *sizes, int **arrs)
{
	int i = 0, count = 0;
	struct Pair* element;

	for (i = 0; i < q.cap; i++)
	{
		element->value = arrs[i][0];
		element->index = i;
		Insert(element);
		count += sizes[i];
	}

	for (i = 0; i < count; i++)
	{
		printf("%d ", ExtractMin());

		sizes[element->index]--;
		if (sizes[element->index])
		{
			++arrs[element->index];
			element->value = *arrs[element->index];
			Insert(element);
		}
	}
}

/*void IncreaseKey(Pair ptr, int newKey)
{
	int i;
	i = ptr.index;

	ptr.key = newKey;

	while(i > 0 && q.heap[ (i - 1) / 2 ].key < newKey)
	{
		Swap(q.heap[ (i - 1) / 2 ], q.heap[i]);  //  !
		q.heap[i].index = i;
		i = (i - 1) / 2;		
	}

	ptr.index = i;
}*/

int main(int argc, char const *argv[])
{
	int i = 0, j = 0;

	int k;
	scanf("%d", &k);

	int sizes[k];

	int sum = 0;

	for (i = 0; i < k; ++i)
	{
		scanf("%d", &sizes[i]);
		sum += sizes[i];
	}

	int **arrs = (int **) malloc (k * sizeof(int *) + sum * sizeof(int));

	for (i = 0; i < k; i++)
	{
		if (i == 0)
			arrs[i] = (int *)(arrs + k);
		else
			arrs[i] = (int *)(arrs[i - 1] + sizes[i - 1]);

		for (j = 0; j < sizes[i]; j++)
			scanf("%d", arrs[i] + j);
	}

	InitPriorityQueue(k);
	QueueProcess(sizes, arrs);

	free(arrs);
	free(q.heap);
	return 0;
}