#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
    if (x >= y) {
        return x;
    }
    return y;
}

void ert(int* p, int size, int x) {
    for (int i = 0; i < size; i++) {
        if (((*(p + i) % x) == 0) && (*(p + i) != x) && *(p + i) != 0) {
            *(p + i) = 0;
        }
    }
}

int mpdiv(int* p, int size, int x) {
    for (int i = size - 1; i >= 0; i--) {
        if (p[i] != 0) {
            if (x % p[i] == 0)
            return max(p[i], mpdiv(p, size, x / p[i]));
        }
    }
    return abs(x);
}

int main(int argc, char **argv)
{
    int x;
    scanf("%d", &x);
    if (x == 0) {
        printf("0\n");
    }
    else {
        int p[46341];
        for (int i = 2; i <= 46341; i++) {
            p[i - 2] = i;
        }
        for (int i = 0; i < 46341; i++) {
            if (p[i] != 0) {
                ert(p, 46341, p[i]);
            }
        }
        printf("%d", mpdiv(p, 46341, x));
        printf("\n");
    }
    return 0;
}