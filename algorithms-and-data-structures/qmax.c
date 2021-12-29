#include <stdio.h>
#include <string.h>
#define STACK_MAX_SIZE 50000

long long max (long long a, long long b) {
	return a > b ? a : b;
}

struct Stack {
	long long elems[STACK_MAX_SIZE][2];
	int top;
};

struct Queue {
	struct Stack head_stack;
	struct Stack tail_stack;
};

void InitStack (struct Stack *stack) {
	stack->top = 0;
}

int is_empty(struct Stack *stack) {
	return stack->top == 0;
}

void push(struct Stack *stack, long long x) {
	if (is_empty(stack)) {
		stack->elems[stack->top][0] = x;
		stack->elems[stack->top][1] = x;
	}
	else {
		stack->elems[stack->top][0] = x;
		stack->elems[stack->top][1] = max(x, stack->elems[stack->top - 1][1]);
	}
	stack->top++;
}

long long pop(struct Stack *stack) {
	stack->top -= 1;
	return stack->elems[stack->top][0];
}

long long get_max(struct Stack *stack) {
	if (is_empty(stack)) return -2000000000;
	return stack->elems[stack->top - 1][1];
}

void InitQueue (struct Queue *queue) {
	InitStack(&queue->head_stack);
	InitStack(&queue->tail_stack);
}

void Enqueue (struct Queue *queue, long long x) {
	push(&queue->head_stack, x);
}

long long Dequeue (struct Queue *queue) {
	if (is_empty(&queue->tail_stack)) {
		while (!is_empty(&queue->head_stack)) {
			push(&queue->tail_stack, pop(&queue->head_stack));
		}
	}
	return pop(&queue->tail_stack);
}

long long Maximum (struct Queue *queue) {
	return max(get_max(&queue->head_stack), get_max(&queue->tail_stack));
}

int QueueEmpty (struct Queue *queue) {
	return (queue->head_stack.top == 0 && queue->tail_stack.top == 0);
}

int main(int argc, char const *argv[])
{
	struct Queue queue;
	InitQueue(&queue);
	int n;
	long long x;
	scanf("%d", &n);
	char op[100];
	for (int i = 0; i < n; ++i) {
		scanf("%s", op);
		if (!strcmp(op, "ENQ")) {
			scanf("%lld", &x);
			Enqueue(&queue, x);
		}
		else if (!strcmp(op, "DEQ")) {
			printf("%lld\n", Dequeue(&queue));
		}
		else if (!strcmp(op, "MAX")) {
			printf("%lld\n", Maximum(&queue));
		}
		else if (!strcmp(op, "EMPTY")) {
			if (QueueEmpty(&queue)) printf("true\n");
			else printf("false\n");
		}
	}
	return 0;
}