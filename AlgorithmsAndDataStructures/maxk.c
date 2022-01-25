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
    int temp = 0;
    int p = 0;
    for (int i = 0; i < k; i++) {
        temp += a[i];
    }
    int msum = temp;
    for (int i = k; i < n; i++) {
        if (temp > msum) {
            msum = temp;
        }
        temp += (a[i] - a[p]);
        p++;
    }
    if (temp > msum) {
        msum = temp;
    }
    printf("%d\n", msum);
    return 0;
}