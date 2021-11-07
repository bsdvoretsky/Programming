#include <stdio.h>

long long int modulo (long long int a, int bb[64], long long int m, int i) {
    if (i == 0) {
        return a * bb[i];
    }
    else {
        return (((2 * (modulo(a, bb, m, i - 1) % m)) % m) + ((a * bb[i]) % m)) % m;
    }
}

int main(int argc, char **argv)
{
    long long int a, b, m;
    scanf("%lld %lld %lld", &a, &b, &m);
    int bb[64];
    long long int i = b;
    int j = 63;
    while (j >= 0)
    {
        bb[j] = i % 2;
        i /= 2;
        j--;
    }
    printf("%lld\n", modulo(a, bb, m, 63));
    return 0;
}