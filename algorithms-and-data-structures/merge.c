#include <stdio.h>
#include <stdlib.h>

struct Pair
{
	int index;
	int value;
};

struct PQ
{
	struct Pair **heap;
	int cap;
	int count;
};

void InitPQ(struct PQ *pq, int k) {
	pq->heap = (struct Pair **) malloc(k * sizeof(struct Pair *));
	pq->cap = k;
	pq->count = 0;
}

void Insert(struct PQ *pq, struct Pair *ptr) {
	int i = pq->count;
	pq->count = i + 1;
	pq->heap[i] = ptr;
	struct Pair *swapper;

	while (i > 0 && (pq->heap[(i - 1) / 2]->value > pq->heap[i]->value)) {
		swapper = pq->heap[(i - 1) / 2];
		pq->heap[(i - 1) / 2] = pq->heap[i];
		pq->heap[i] = swapper;

		pq->heap[i]->index = i;
		i = (i - 1) / 2;
	}
	pq->heap[i]->index = i;
}

void Heapify(int i, int k, struct Pair **heap) {
	int l, r, j;
	struct Pair *swapper;

	for (;;) {
		l = 2 * i + 1;
		r = l + 1;
		j = i;

		if (l < k && heap[i]->value > heap[l]->value)
			i = l;
		if (r < k && heap[i]->value > heap[r]->value)
			i = r;
		if (i == j) 
			break;

		swapper = heap[i];
		heap[i] = heap[j];
		heap[j] = swapper;

		heap[i]->index = i;
		heap[j]->index = j;
	}
}

struct Pair* ExtractMin(struct PQ *pq) {
	struct Pair *ptr = pq->heap[0];
	--(pq->count);

	if (pq->count > 0) {
		pq->heap[0] = pq->heap[pq->count];
		pq->heap[0]->index = 0;
		Heapify(0, pq->count, pq->heap);
	}
}

int main(int argc, char const *argv[])
{
	int i = 0, j = 0, k, sum = 0;
	int sizes[k];

	scanf("%d", &k);

	for (i = 0; i < k; ++i)
	{
		scanf("%d", &sizes[i]);
		sum += sizes[i];
	}

	int *arrs[k];
	for (i = 0; i < k; i++)
	{
		arrs[i] = malloc(sizes[i] * sizeof(int));

		for (j = 0; j < sizes[i]; j++)
			scanf("%d", arrs[i][j]);
	}

	struct PQ pq;
	InitPQ(&pq, k);

	int count = 0;
	struct Pair *temp;

	for (i = 0; i < k; ++i) {
		temp = (struct Pair *) malloc (sizeof(struct Pair));
		temp->value = arrs[i][0];
		temp->index = i;
		Insert(&pq, temp);
		count += sizes[i];
	}

	struct Pair *element;

	for (i = 0; i < count; i++)
	{
		element = (struct Pair *) malloc (sizeof(struct Pair));
		element = ExtractMin(&pq);
		printf("%d ", element->value);

		--sizes[element->index];
		if (sizes[element->index])
		{
			++arrs[element->index];
			element->value = arrs[element->index][0];
			Insert(&pq, element);
		}
	}

	return 0;
}