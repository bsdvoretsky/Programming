#include <stdio.h>
#include <stdlib.h>
#define STACK_MAX_SIZE 100

struct Task {
    int low, high;
};

struct Stack {
	struct Task tasks[STACK_MAX_SIZE];
	int top;
};

void init(struct Stack *stack) {
	stack->top = 0;
}

void push(struct Stack *stack, struct Task task) {
	if (stack->top < STACK_MAX_SIZE) {
		stack->tasks[stack->top] = task;
		stack->top++;
	}
	else {
		printf("Stack full, the number of elements is %d!\n", stack->top);
	}
}

struct Task pop(struct Stack *stack) {
	if (stack->top > 0) {
		stack->top--;
		return stack->tasks[stack->top];
	}
	else {
		printf("Stack is empty!\n");
	}
}

int is_empty (struct Stack *stack) {
	return (stack->top == 0);
}

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	struct Stack stack;
	struct Task cur_task;
	int mid, k = 0, p, t;
	int *b;
	init(&stack);
	struct Task temp_task = {0, n};
	push(&stack, temp_task);
	
	while (!is_empty(&stack)) {
		cur_task = pop(&stack);
		if (cur_task.low != cur_task.high) {
			b = (int *) calloc (cur_task.high - cur_task.low, sizeof(int));
			mid = (cur_task.high + cur_task.low) / 2;
			for (int i = cur_task.low; i < cur_task.high; ++i) {
				if (a[i] < a[mid]) {
					b[k] = a[i];
					k++;
				}
			}
			p = cur_task.low + k;
			for (int i = cur_task.low; i < cur_task.high; ++i) {
				if (a[i] == a[mid]) {
					b[k] = a[i];
					k++;
				}
			}
			t = cur_task.low + k;
			for (int i = cur_task.low; i < cur_task.high; ++i) {
				if (a[i] > a[mid]) {
					b[k] = a[i];
					k++;
				}
			}
			for (int i = cur_task.low; i < cur_task.high; ++i) {
				a[i] = b[i - cur_task.low];
			}
			temp_task.low = cur_task.low;
			temp_task.high = p;
			push(&stack, temp_task);
			temp_task.low = t;
			temp_task.high = cur_task.high;
			push(&stack, temp_task);
			free(b);
			k = 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	return 0;
}