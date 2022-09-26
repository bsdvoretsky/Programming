#include <stdio.h>

int a[] = {5, 1, 2, 3, 4, 7, 4};

int less(unsigned long i, unsigned long j) {
    if (a[i] < a[j]) return 1;
    return 0;
}

unsigned long peak(unsigned long nel,
        int (*less)(unsigned long i, unsigned long j))
{
        for (unsigned long i = 0; i < nel; i++) {
            if (i == 0) {
                if (less(0, 1) == 0) return i;
            }
            else if (i == nel - 1) {
                if (less(nel - 1, nel - 2) == 0) return i;
            }
            else {
                if (less(i, i - 1) == 0 && less(i, i + 1) == 0) return i;
            }
        }
}


int main(int argc, char **argv)
{
    printf("%lu\n", peak(7, less)); // 0
    return 0;
}