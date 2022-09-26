#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	size_t t1;
	size_t t2;
} task;

struct Queue
{
	size_t *heap;
	size_t cnt, cap, timeWork;
} q;

int Compare(size_t a, size_t b)
{
	if (q.heap[a] == q.heap[b])
		return 0;

	return (q.heap[a] > q.heap[b]) ? 1 : -1;
}

void Swap(size_t a, size_t b)
{
	size_t tmp = q.heap[a];
	q.heap[a] = q.heap[b];
	q.heap[b] = tmp;
}

void ClusterInit(size_t n)
{
	q.heap = (size_t *)malloc(n * sizeof(size_t));
	q.cap = n;
	q.cnt = 0;
	q.timeWork = 0;
}

size_t Parent(size_t idx)
{
	return (idx - 1) >> 1;
}

size_t ChildLeft(size_t idx)
{
	return (idx << 1) + 1;
}

size_t ChildRight(size_t idx)
{
	return (idx << 1) + 2;
}

void SiftDown()
{
	size_t idx = 0, idx_min = 0, left = 0, right = 0;

	while (1)
	{
		idx = idx_min;
		left = ChildLeft(idx);
		right = ChildRight(idx);

		if (left < q.cnt && Compare(idx_min, left) == 1)
			idx_min = left;

		if (right < q.cnt && Compare(idx_min, right) == 1)
			idx_min = right;

		if (idx_min == idx)
			break;

		Swap(idx, idx_min);
	}
}

void SiftUp(size_t idx)
{
	while (idx && Compare(Parent(idx), idx) == 1)
	{
		Swap(Parent(idx), idx);
		idx = Parent(idx);
	}
}

void ClusterTimeWorkUpdate(size_t idx)
{
	if (q.timeWork < q.heap[idx])
		q.timeWork = q.heap[idx];
}

void ClusterInsert(task element)
{
	size_t idx = q.cnt;

	if (q.cnt == q.cap)
	{
		if (element.t1 <= q.heap[0])
			q.heap[0] += element.t2;
		else
			q.heap[0] += (element.t1 - q.heap[0] + element.t2);

		ClusterTimeWorkUpdate(0);
		SiftDown(0);
	}
	else
	{
		q.heap[idx] = element.t1 + element.t2;
		q.cnt++;
		ClusterTimeWorkUpdate(idx);
		SiftUp(idx);
	}
}

size_t ClusterProcess(task *tasks, size_t m)
{
	for (size_t i = 0; i < m; i++)
		ClusterInsert(tasks[i]);

	return q.timeWork;
}

int main()
{
	size_t n = 0, m = 0, i = 0;
	scanf("%u %u", &n, &m);

	if (n > m)
		n = m;

	task *tasks = malloc(m * sizeof(task));

	for (i = 0; i < m; i++)
		scanf("%u %u", &tasks[i].t1, &tasks[i].t2);

	ClusterInit(n);
	printf("%u\n", ClusterProcess(tasks, m));

	free(tasks);
	free(q.heap);
	return 0;
}