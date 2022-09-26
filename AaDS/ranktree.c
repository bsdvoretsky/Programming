#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VAL_LEN 10

typedef struct Node
{
	int k;
	char v[VAL_LEN];
	int count;
	struct Node *parent, *left, *right;
} t_node;

t_node* NodeInit(int k, char* v)
{
	t_node *n = (t_node*)malloc(sizeof(t_node));
	n->k = k;
	strcpy(n->v, v);
	n->count = 1;
	n->parent = n->left = n->right = NULL;

	return n;
}

typedef struct Tree
{
	t_node *head;
} t_tree;

t_tree* TreeInit()
{
	t_tree *tnew = (t_tree*)malloc(sizeof(t_tree));
	tnew->head = NULL;

	return tnew;
}

int Compare(int a, int b)
{
	if (a == b)
		return 0;

	return (a > b) ? 1 : -1;
}

t_node* TreeMin(t_node *t)
{
	t_node *n;

	if (t == NULL)
		n = NULL;
	else
	{
		n = t;

		while (n->left != NULL)
			n = n->left;
	}

	return n;
}

t_node* NodeNext(t_node *n)
{
	t_node *ret = n;

	if (n->right)
		ret = TreeMin(n->right);
	else
	{
		ret = n->parent;

		while (ret && n == ret->right)
		{
			n = ret;
			ret = ret->parent;
		}
	}

	return ret;
}

t_node* NodeLookup(t_tree *t, int k)
{
	t_node *ret = t->head;

	while (ret && Compare(ret->k, k))
	{
		if (Compare(ret->k, k) == 1)
			ret = ret->left;
		else
			ret = ret->right;
	}

	return ret;
}

t_tree* NodeReplace(t_tree *t, t_node *i, t_node *j)
{
	if (i == t->head)
	{
		t->head = j;
		j->parent = NULL;

		return t;
	}

	t_node *par = i->parent;

	if (j)
		j->parent = par;

	if (par->left == i)
		par->left = j;
	else
		par->right = j;

	return t;
}

void TreeCountDec(t_node *node)
{
	t_node *n = node->parent;

	while (n)
	{
		n->count--;
		n = n->parent;
	}
}

t_tree* NodeDelete(t_tree *t, int k)
{
	t_node *i = NodeLookup(t, k);
	t_node *j;

	if (i->left && i->right)
	{
		j = NodeNext(i);
		TreeCountDec(j);
		NodeReplace(t, j, j->right);
		i->left->parent = j;
		j->left = i->left;

		if (i->right)
			i->right->parent = j;

		j->right = i->right;
		j->count = i->count;
		NodeReplace(t, i, j);
	}
	else
	{
		TreeCountDec(i);

		if (!i->left && !i->right)
			NodeReplace(t, i, NULL);
		else if (!i->left)
			NodeReplace(t, i, i->right);
		else if (!i->right)
			NodeReplace(t, i, i->left);
	}

	free(i);
	return t;
}

int NodeRank(t_node *node)
{
	return (node->left ? node->left->count : 0);
}

t_node* NodeSearch(t_tree *t, int k)
{
	t_node *ret = t->head;

	while (NodeRank(ret) != k)
	{
		while (Compare(NodeRank(ret), k) == 1)
			ret = ret->left;
		while (Compare(NodeRank(ret), k) == -1)
		{
			k -= NodeRank(ret) + 1;
			ret = ret->right;
		}
	}

	return ret;
}

t_node* NodeInsert(t_tree *t, int k, char* v)
{
	t_node *node = NodeInit(k, v);

	if (!t->head)
	{
		t->head = node;
		return node;
	}

	t_node *ntmp = t->head;

	while (1)
	{
		ntmp->count++;

		if (Compare(k, ntmp->k) == -1)
		{
			if (!ntmp->left)
			{
				ntmp->left = node;
				node->parent = ntmp;
				node->count += NodeRank(node);
				break;
			}
			else
				ntmp = ntmp->left;
		}
		else
		{
			if (!ntmp->right)
			{
				ntmp->right = node;
				node->parent = ntmp;
				node->count += NodeRank(node);
				break;
			}
			else
				ntmp = ntmp->right;
		}
	}

	return node;
}

void NodesFree(t_node *n)
{
	if (n)
	{
		NodesFree(n->left);
		NodesFree(n->right);
		free(n);
		n = NULL;
	}
}

int main(int argc, char **argv)
{
	int n = 0, i = 0;
	scanf("%d", &n);

	t_tree *t = TreeInit();

	char cmd[VAL_LEN] = { 0 };
	char v[VAL_LEN] = { 0 };
	int k;

	for (i = 0; i < n; i++)
	{
		scanf("%s %d", cmd, &k);

		if (strcmp(cmd, "INSERT") == 0)
		{
			scanf("%s", v);
			NodeInsert(t, k, v);
		}
		else if (strcmp(cmd, "LOOKUP") == 0) printf("%s\n", NodeLookup(t, k)->v);
		else if (strcmp(cmd, "SEARCH") == 0) printf("%s\n", NodeSearch(t, k)->v);
		else if (strcmp(cmd, "DELETE") == 0) NodeDelete(t, k);
		else return 1;
	}

	NodesFree(t->head);
	free(t);
	t = NULL;
	return 0;
}