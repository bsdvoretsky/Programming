#include <stdio.h>
#include <stdlib.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

int main (int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    union Int32 a[n];
    int temp[n];
    int k = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].x);
    }
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < n; j++) {
            if (((a[j].bytes[i / 8] & 1<<(i % 8))==1<<(i % 8)) == 0) {
                temp[k] = a[j].x;
                k++;
            }
        }
        for (int j = 0; j < n; j++) {
            if (((a[j].bytes[i / 8] & 1<<(i % 8))==1<<(i % 8)) == 1) {
                temp[k] = a[j].x;
                k++;
            }
        }
        for (int l = 0; l < n; l++) {
            a[l].x = temp[l];
        }
        k = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (a[i].x < 0)
            printf("%d ", a[i].x);
    }
    for (int i = 0; i < n; ++i) {
        if (a[i].x >= 0)
            printf("%d ", a[i].x);
    }
    
    return 0;
}