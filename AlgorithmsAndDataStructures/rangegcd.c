#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int n1, int n2)
{
    n1 = abs(n1);
    n2 = abs(n2);

    int a, b;

    if (n1 > n2)
    {
        a = n1;
        b = n2;
    }
    else
    {
        a = n2;
        b = n1;
    }

    if (!b)
        return a;

    int r1 = a % b, r2 = b;

    while (r1)
    {
        a = b;
        b = r2 = r1;
        r1 = a % b;
    }

    return r2;
}

int *arr;
int **table;

int** SparseTableInit(size_t n)
{
    int j = 0, m = (int)log2(n) + 1;
    size_t i = 0;

    table = (int **)calloc(1, n * sizeof(int *) + n * m * sizeof(int));
    table[0] = (int *)(table + n);

    for (i = 1; i < n; i++)
        table[i] = table[i - 1] + m;

    for (i = 0; i < n; i++)
        table[i][0] = arr[i];

    for (j = 1; j < m; ++j)
    {
        for (i = 0; i <= (n - (1 << j)); i++)
            table[i][j] = gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    return table;
}

int SparseTableQuery(int l, int r)
{
    int m = (int)log2(r - l + 1);

    return gcd(table[l][m], table[r - (1 << m) + 1][m]);
}

int main(int argc, char **argv)
{
    size_t n = 0, i = 0;
    scanf("%u", &n);

    arr = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", arr + i);

    SparseTableInit(n);

    int l = 0, r = 0;
    size_t m = 0;
    scanf("%u", &m);

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &l, &r);
        printf("%d\n", SparseTableQuery(l, r));
    }

    free(table);
    free(arr);
    arr = NULL;

    return 0;
}