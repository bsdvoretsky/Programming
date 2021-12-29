#include <stdio.h>

unsigned long long modulo (long int a, int bb[64], long int m, int i) {
    if (i == 63) {
        return a * bb[i];
    }
    return ((modulo(a, bb, m, i + 1) * 2) % m + (a * bb[i]) % m) % m;
}

int main(int argc, char **argv)
{
    unsigned long long a, b, m;
    scanf("%llu %llu %llu", &a, &b, &m);
    int bb[64];
    int j = 0;
    while (j < 64)
    {
        bb[j] = b % 2;
        b /= 2;
        j++;
    }
    printf("%llu\n", modulo(a, bb, m, 0));
    return 0;
} 