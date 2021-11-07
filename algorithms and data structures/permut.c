#include <stdio.h>

int count(int x, int* a) {
    int i = 0;
    for (int j = 0; j < 8; j++) {
        if (*(a + j) == x) {
            i++;
        }
    }
    return i;
}

int main(int argc, char **argv)
{
    int a[8], b[8], f = 1;
    for (int i = 0; i < 8; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < 8; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < 8; i++) {
        if (count(a[i], b) != count(a[i], a)) {
            printf("no\n");
            f = 0;
            break;
        }
    }
    if (f == 1) {
        printf("yes\n");
    }
    return 0;
}