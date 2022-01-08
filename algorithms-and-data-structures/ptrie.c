#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_SIZE 26

struct Trie {
	int endmark;
	struct Trie *next[CHAR_SIZE];
};

struct Trie* getNewTrieNode()
{
    struct Trie* node = (struct Trie*) malloc (sizeof(struct Trie));
    node->endmark = 0;
 
    for (int i = 0; i < CHAR_SIZE; i++) {
        node->next[i] = NULL;
    }
 
    return node;
}

void Insert (struct Trie *root, char *str) {
	struct Trie *curr = root;
	while (*str)
    {
        if (curr->next[*str - 'a'] == NULL) {
            curr->next[*str - 'a'] = getNewTrieNode();
        }
        curr = curr->next[*str - 'a'];
        str++;
    }
    curr->endmark += 1;
}

int hasChildren(struct Trie* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->next[i]) {
            return 1;
        }
    }
 
    return 0;
}

int Delete(struct Trie **curr, char* str)
{
    if (*curr == NULL) {
        return 0;
    }
 
    if (*str)
    {
        if (*curr != NULL && (*curr)->next[*str - 'a'] != NULL &&
            Delete(&((*curr)->next[*str - 'a']), str + 1) &&
            (*curr)->endmark == 0)
        {
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else {
                return 0;
            }
        }
    }
 
    if (*str == '\0' && (*curr)->endmark)
    {
    	if ((*curr)->endmark > 1) {
    		(*curr)->endmark--;
    		return 0;
    	}
    	else {
	        if (!hasChildren(*curr))
	        {
	            free(*curr); 
	            (*curr) = NULL;
	            return 1;
	        }
	        else {
	            (*curr)->endmark = 0;
	            return 0;
	        }
    	}
    }

    return 0;
}

int countOfChilds(struct Trie **curr) {
	if (*curr == NULL) {
        return 0;
    }

    int s = (*curr)->endmark;
    for (int i = 0; i < CHAR_SIZE; ++i) {
    	s += countOfChilds(&((*curr)->next[i]));
    }
    return s;
}

int Prefix(struct Trie* root, char* str)
{
    if (root == NULL) {
        return 0;
    }
 
    struct Trie* curr = root;
    while (*str)
    {
        curr = curr->next[*str - 'a'];
 
        if (curr == NULL) {
            return 0;
        }
 
        str++;
    }

    return countOfChilds(&curr);
}


int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	char op[7];
	char *k = (char *) calloc (100000, sizeof(char));
	struct Trie *root = getNewTrieNode();

	for (int i = 0; i < n; ++i) {
		scanf("%s", op);
		scanf("%s", k);
		if (!strcmp(op, "INSERT")) {
			Insert(root, k);
		}
		else if (!strcmp(op, "DELETE")) {
			Delete(&root, k);
		}
		else if (!strcmp(op, "PREFIX")) {
			printf("%d\n", Prefix(root, k));
		}
	}

    free(k);
    free(root);
	return 0;
}