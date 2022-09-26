#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_SIZE 26

struct Trie {
    int count;
    struct Trie *next[CHAR_SIZE];
};

struct Trie* getNewTrieNode()
{
    struct Trie* node = (struct Trie*) malloc (sizeof(struct Trie));
    node->count = 0;
 
    for (int i = 0; i < CHAR_SIZE; i++) {
        node->next[i] = NULL;
    }
 
    return node;
}

int Search(struct Trie *root, char *str) {
    if (root == NULL)
        return 0;
    if (*str == '\0')
        return 1;
    else 
        return Search(root->next[*str - 'a'], str + 1);
}

void Insert (struct Trie *root, char *str) {
    struct Trie *curr = root;
    while (*str)
    {
        if (curr->next[*str - 'a'] == NULL) {
            curr->next[*str - 'a'] = getNewTrieNode();
        }
        curr = curr->next[*str - 'a'];
        curr->count++;
        str++;
    }
}

int Delete(struct Trie **curr, char* str)
{ 
    (*curr)->count--;

    if (*str == '\0')
    {
        return 1;
    }

    return Delete(&(*curr)->next[*str - 'a'], str + 1);
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

    return curr->count;
}

void FreePtrie(struct Trie* root) {
    if (root) {
        for (int i = 0; i < CHAR_SIZE; ++i)
            FreePtrie(root->next[i]);
        free(root);
    }
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
            if (root == NULL) {
                root = getNewTrieNode();
            }
            if (!Search(root, k))
                Insert(root, k);
        }
        else if (!strcmp(op, "DELETE")) {
            Delete(&root, k);
        }
        else if (!strcmp(op, "PREFIX")) {
            printf("%d ", Prefix(root, k));
        }
    }
    printf("\n");
    free(k);
    FreePtrie(root);
    return 0;
}