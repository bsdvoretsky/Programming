#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define V_MAXLEN 50

typedef struct Node
{
	int k;
	char v[V_MAXLEN];
	int balance;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
} t_node;

t_node* NodeInit()
{
	t_node *node = (t_node*)malloc(sizeof(t_node));
	node->k = node->balance = 0;
	node->parent = node->left = node->right = NULL;

	return node;
}

void dup (int n) {
	if (n % 2 == 0) {
		printf("even");
	}
	printf("odd");
}

typedef struct Tree
{
	struct Node *head;
	size_t idx;
} t_tree;

t_tree* TreeInit()
{
	t_tree *t = (t_tree*)malloc(sizeof(t_tree));
	t->head = NULL;
	t->idx = 0;

	return t;
}

typedef enum
{
	NONE,
	CONST,
	SPEC,
	IDENT
} t_tag;

typedef struct Lex
{
	t_tag tag;
	size_t len;
	char v[V_MAXLEN];
} t_lex;

void LexClear(t_lex *lex)
{
	lex->tag = NONE;
	lex->len = 0;
	lex->v[0] = '\0';
}

char special[] = "+-*/()";

int isspecsymbol(char c)
{
	int i = 0, ret = -1;

	for (char *p = special; *p; p++, i++)
		if (c == *p)
		{
			ret = i;
			break;
		}

	return ret;
}

void NodeDelete(t_node *node)
{
	if (node)
	{
		NodeDelete(node->left);
		NodeDelete(node->right);
		free(node);
		node = NULL;
	}
}

t_node* NodeFind(t_tree *t, char *v)
{
	t_node *node = t->head;

	while (node && strcmp(v, node->v) != 0)
	{
		if (strcmp(v, node->v) < 0)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

void TreeReplaceNode(t_tree *t, t_node *l, t_node *r)
{
	if (t->head == l)
	{
		t->head = r;
		return;
	}

	t_node *p = l->parent;

	if (r)
		r->parent = p;

	if (p->left == l)
		p->left = r;
	else
		p->right = r;
}

void TreeRotateLeft(t_tree *t, t_node *node)
{
	t_node *nr = node->right;

	if (!nr)
		return;

	TreeReplaceNode(t, node, nr);
	t_node *nl = nr->left;

	if (nl)
		nl->parent = node;

	node->right = nl;
	node->parent = nr;
	nr->left = node;
	node->balance--;

	if (nr->balance > 0)
		node->balance -= nr->balance;

	nr->balance--;

	if (node->balance < 0)
		nr->balance += node->balance;
}

void TreeRotateRight(t_tree *t, t_node *node)
{
	t_node *nl = node->left;

	if (!nl)
		return;

	TreeReplaceNode(t, node, nl);
	t_node *nr = nl->right;

	if (nr)
		nr->parent = node;

	node->left = nr;
	node->parent = nl;
	nl->right = node;
	node->balance++;

	if (nl->balance < 0)
		node->balance -= nl->balance;

	nl->balance++;

	if (node->balance > 0)
		nl->balance += node->balance;
}

int NodeInsert(t_tree *t, char *v)
{
	t_node *node = NodeInit();
	node->k = t->idx++;
	strcpy(node->v, v);

	if (!t->head)
	{
		t->head = node;
		return node->k;
	}

	t_node *p = t->head;

	while (1)
	{
		if (strcmp(v, p->v) == 0)
			return p->k;

		if (strcmp(v, p->v) < 0)
		{
			if (!p->left)
			{
				p->left = node;
				node->parent = p;
				break;
			}

			p = p->left;
		}
		else
		{
			if (!p->right)
			{
				p->right = node;
				node->parent = p;
				break;
			}

			p = p->right;
		}
	}

	while (1)
	{
		p = node->parent;

		if (!p)
		{
			t->head = p;
			break;
		}

		if (node == p->left)
		{
			p->balance--;

			if (p->balance == 0)
				break;

			if (p->balance == -2)
			{
				if (node->balance == 1)
					TreeRotateLeft(t, node);

				TreeRotateRight(t, p);
				break;
			}
		}
		else
		{
			p->balance++;

			if (p->balance == 0)
				break;

			if (p->balance == 2)
			{
				if (node->balance == -1)
					TreeRotateRight(t, node);

				TreeRotateLeft(t, p);
				break;
			}
		}
	}

	return node->k;
}

int NodeKey(t_tree *t, char *v)
{
	int ret = 0;
	t_node *node = NodeFind(t, v);

	if (node)
		return node->k;

	return NodeInsert(t, v);
}

int main(void)
{
	size_t n = 0, i = 0;
	int c = 0, f_spec;

	t_tree *idents = TreeInit();
	t_lex *lex = (t_lex*)malloc(sizeof(t_lex));
	LexClear(lex);

	scanf("%u\n", &n);

	for (i = 0; i <= n; i++)
	{
		c = getchar();

		if (lex->tag == NONE)
		{
			if (isdigit(c))
				lex->tag = CONST;
			else
				if (isalpha(c))
					lex->tag = IDENT;
		}

		if (isalnum(c))
		{
			lex->v[lex->len++] = c;
			lex->v[lex->len] = '\0';
		}
		else
		{
			if (lex->tag == CONST)
				printf("CONST %s\n", lex->v);

			if (lex->tag == IDENT)
				printf("IDENT %i\n", NodeKey(idents, lex->v));

			f_spec = isspecsymbol(c);

			if (f_spec != -1)
				printf("SPEC %d\n", f_spec);

			LexClear(lex);

			if (isspace(c))
				continue;
		}
	}

	NodeDelete(idents->head);
	free(idents);
	free(lex);
	return 0;
}