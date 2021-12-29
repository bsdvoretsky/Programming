#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a == 0) return abs(b);
    gcd(b % a, a);
}

int gcd_arr(int *a, int b, int e) {
    if (b == e) {
        return a[b];
    }
    int res = gcd(a[b], a[b + 1]);
    for (int i = b + 2; i <= e; ++i) {
        res = gcd(a[i], res);
    }
    return res;
}

int main(int argc, char **argv)
{
    int n, m, l, r;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &l, &r);
        if (l >= r) {
            printf("%d\n", gcd_arr(a, r, l));
        }
        else {
            printf("%d\n", gcd_arr(a, l, r));
        }
    }
    return 0;
}