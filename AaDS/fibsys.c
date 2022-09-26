#include <stdio.h>

void fibsys (long long int x, int *fibx) {
    if (x == 1) {
        *fibx = 1;
    }
    else if (x > 1) {
        long long int i = 1;
        long long int j = 2;
        long long int n = 0;
        long long int t;
        while (i < x) {
            if (j > x) {
                break;
            }
            t = i;
            i = j;
            j = t + j;
            n++;
        }
        *(fibx + n) = 1;
        fibsys(x - i, fibx);
    }
}

int main(int argc, char **argv)
{
    long long int x;
    scanf("%lld", &x);
    if (x == 0) {
        printf("0\n");
    }
    else if (x == 1) {
        printf("1\n");
    }
    else {
        long long int i = 1;
        long long int j = 2;
        long long int n = 0;
        long long int t;
        while (i < x) {
            if (j > x) {
                break;
            }
            t = i;
            i = j;
            j = t + j;
            n++;
        }
        int fibx[n + 1];
        j = 0;
        while (j <= n) {
            if (j == n) {
                fibx[j] = 1;
            }
            else {
                fibx[j] = 0;
            }
            j++;
        }
        fibsys(x - i, fibx);
        i = n;
        while (i >= 0) {
            printf("%d", fibx[i]);
            i--;
        }
        printf("\n");
    }
    
    return 0;
}