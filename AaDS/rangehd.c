#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_MAX 1000001

char *buff;
int *tree;

int TreeBuild(int l, int r, int n)
{
	int m = 0, summ = 0;
	int bound = (r < n) ? r : n;

	while (l < bound)
	{
		m = (l + r) / 2;
		summ ^= TreeBuild(l, m, n);
		l = m + 1;
	}

	if (r < n)
	{
		summ ^= 1 << (((int)buff[r]) - 97);
		tree[r] = summ;
	}

	return summ;
}

void TreeInit(int n)
{
	int r = 1;

	while (r < n)
		r *= 2;

	TreeBuild(0, r - 1, n);
}

int TreeQuery(int i)
{
	int v = 0;

	while (i >= 0)
	{
		v ^= tree[i];
		i = (i&(i + 1)) - 1;
	}

	return v;
}

void TreeUpdate(int i, int delta, int n)
{
	while (i < n)
	{
		tree[i] ^= delta;
		i = i | (i + 1);
	}
}

int main()
{
	buff = (char*)malloc(LEN_MAX * sizeof(char));
	fgets(buff, LEN_MAX, stdin);
	int n = strlen(buff);

	tree = (int*)malloc(n * sizeof(int));
	TreeInit(n);

	int m = 0, i = 0, l = 0, r = 0, k = 0, v = 0;
	scanf("%d", &m);

	char op[4] = { 0 };

	for (k = 0; k < m; k++)
	{
		scanf("%s", op);

		if (strcmp("HD", op) == 0)
		{
			scanf("%d %d", &l, &r);
			v = TreeQuery(r) ^ TreeQuery(l - 1);
			if (((!((r - l + 1) % 2)) && (!v)) || (((r - l + 1) % 2) && (!(v&(v - 1)))))
				printf("YES\n");
			else
				printf("NO\n");
		}
		else
		{
			int delta = 0, ch;
			char *str = (char*)malloc(LEN_MAX * sizeof(char));
			scanf("%d %s", &ch, str);
			int len = strlen(str);
			delta ^= 1 << (((int)buff[ch]) - 97);

			for (i = 0; i < len; i++, ch++)
			{
				delta = (1 << ((int)str[i] - 97)) ^ (1 << (((int)buff[ch]) - 97));
				TreeUpdate(ch, delta, n);
				buff[ch] = str[i];
			}

			free(str);
		}
	}

	free(tree); tree = NULL;
	free(buff); buff = NULL;
	return 0;
}