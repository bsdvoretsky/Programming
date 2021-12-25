#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define STACK_MAX_SIZE 100000

struct Stack {
	long long elems[STACK_MAX_SIZE];
	int top;
};

void init(struct Stack *stack) {
	stack->top = 0;
}

void push(struct Stack *stack, long long d) {
	if (stack->top < STACK_MAX_SIZE) {
		stack->elems[stack->top] = d;
		stack->top++;
	}
	else {
		printf("Stack full, the number of elements is %d!\n", stack->top);
	}
}

long long getup(struct Stack *stack) {
	return stack->elems[stack->top - 1];
}

long long pop(struct Stack *stack) {
	if (stack->top > 0) {
		stack->top--;
		return stack->elems[stack->top];
	}
	else {
		printf("Stack is empty!\n");
	}
}

void add(struct Stack *stack) {
	long long a = pop(stack);
	long long b = pop(stack);
	push(stack, a + b);
}

void sub(struct Stack *stack) {
	long long a = pop(stack);
	long long b = pop(stack);
	push(stack, a - b);
}

void mul(struct Stack *stack) {
	long long a = pop(stack);
	long long b = pop(stack);
	push(stack, a * b);
}

void my_div(struct Stack *stack) {
	long long a = pop(stack);
	long long b = pop(stack);
	push(stack, a / b);
}

void max(struct Stack *stack) {
	long long a = pop(stack);
	long long b = pop(stack);
	if (a >= b) push(stack, a);
	else push(stack, b);
}

void min(struct Stack *stack) {
	long long a = pop(stack);
	long long b = pop(stack);
	if (a <= b) push(stack, a);
	else push(stack, b);
}

void neg(struct Stack *stack) {
	stack->elems[stack->top - 1] *= -1;
}

void dup(struct Stack *stack) {
	push(stack, stack->elems[stack->top - 1]);
}

void swap(struct Stack *stack) {
	long long temp = stack->elems[stack->top - 1];
	stack->elems[stack->top - 1] = stack->elems[stack->top - 2];
	stack->elems[stack->top - 2] = temp;
}



int main(int argc, char const *argv[])
{
	int n, t;
	scanf("%d", &n);
	struct Stack stack;
	init(&stack);
	char op[100];
	for (int i = 0; i < n; ++i) {
		scanf("%s", &op);
		if (strcmp(op, "CONST") == 0) {
			scanf("%ld", &t);
			push(&stack, t);
		}
		else if (strcmp(op, "ADD") == 0) {
			add(&stack);
		}
		else if (strcmp(op, "SUB") == 0) {
			sub(&stack);
		}
		else if (strcmp(op, "MUL") == 0) {
			mul(&stack);
		}
		else if (strcmp(op, "DIV") == 0) {
			my_div(&stack);
		}
		else if (strcmp(op, "MAX") == 0) {
			max(&stack);
		}
		else if (strcmp(op, "MIN") == 0) {
			min(&stack);
		}
		else if (strcmp(op, "NEG") == 0) {
			neg(&stack);
		}
		else if (strcmp(op, "DUP") == 0) {
			dup(&stack);
		}
		else if (strcmp(op, "SWAP") == 0) {
			swap(&stack);
		}
	}
	printf("%ld", getup(&stack));
	return 0;
}