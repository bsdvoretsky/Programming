#include <stdio.h>
#include <stdlib.h>

int compare (void* a, void* b) {
    if (*((int*) a) > *((int*) b)) return 1;
    else if (*((int*) a) == *((int*) b)) return 0;
    else return -1;
}

int maxarray(void* base, size_t nel, size_t width,
        int (*compare)(void *a, void *b))
{
        int idx = 0;
        int* max = &*((int*) base);
        int* cur = &*((int*) base);
        for (size_t i = 1; i < nel; ++i) {
            cur += 1;
            if (compare(cur, max) > 0) {
                idx = i;
                max = cur;
            }
        }
        return idx;
}


int main(int argc, char **argv)
{
    int arr[] = {8, 7, 7, 7, 10, 6, 5, 4, 3, 2, 1};
    printf("%d\n", maxarray(arr, 9, sizeof(int), compare));
    return 0;
}