#include <stdio.h>
#include <math.h> 

int main(int argc, char **argv)
{
    int an, bn, a = 0, b = 0, c, t;
    scanf("%d", &an);
    for (int i = 0; i < an; i++) {
        scanf("%d", &t);
        a = a | (int) pow(2, t);
    }
    scanf("%d", &bn);
    for (int i = 0; i < bn; i++) {
        scanf("%d", &t);
        b = b | (int) pow(2, t);
    }
    c = a & b;
    for (int i = 1; i < 32; i++) {
        if ((c & (int) pow(2, i)) != 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}