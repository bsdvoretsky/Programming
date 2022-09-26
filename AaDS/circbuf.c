#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Queue {
	long long *elems;
	int size;
	int last;
};

void InitQueue(struct Queue *queue) {
	queue->elems = (long long *) calloc (4, sizeof(long long));
	queue->last = 0;
	queue->size = 4;
}

int QueueEmpty(struct Queue *queue) {
	if (queue->last == 0) return 1;
	return 0;
}

void Enqueue (struct Queue *queue, long long d) {
	if (queue->last == queue->size) {
		queue->elems = (long long *) realloc (queue->elems, queue->size * 2  * sizeof(long long));
		queue->size *= 2;
	}
	queue->elems[queue->last] = d;
	queue->last++;
}

long long Dequeue (struct Queue *queue) {
	long long first = queue->elems[0];
	for (int i = 0; i < queue->size - 1; ++i) {
		queue->elems[i] = queue->elems[i + 1];
	}
	queue->last--;
	return first;
}

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	char op[100];
	long long d;
	struct Queue queue;
	InitQueue(&queue);
	for (int i = 0; i < n; ++i) {
		scanf("%s", op);
		if (strcmp(op, "ENQ") == 0) {
			scanf("%lld", &d);
			Enqueue(&queue, d);
		}
		else if (strcmp(op, "DEQ") == 0) {
			printf("%lld\n", Dequeue(&queue));
		}
		else if (strcmp(op, "EMPTY") == 0) {
			if (QueueEmpty(&queue)) printf("true\n");
			else printf("false\n");
		}
	}
	free(queue.elems);
	return 0;
}