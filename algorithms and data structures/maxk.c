#include <stdio.h>

int main(int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int k;
    scanf("%d", &k);
    int msum = 0;
    int* b = a;
    for (int i = 0; i < k; i++) {
        msum += a[i];
    }
    for (int i = k; i < n; i++) {
        if ((a[k] - *b) > 0) {
            msum += (a[i] - *b);
        }
        b++;
    }
    printf("%d\n", msum);
    return 0;
}