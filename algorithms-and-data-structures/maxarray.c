#include <stdio.h>
#include <stdlib.h>

int maxarray(void* base, size_t nel, size_t width,
        int (*compare)(void *a, void *b))
{
        int idx = 0;
        char *max = (char*) base;
        char *cur = (char*) base;
        for (size_t i = 1; i < nel; ++i) {
            cur += width;
            if (compare(cur, max) > 0) {
                idx = i;
                max = cur;
            }
        }
        return idx;
}

int main(int argc, char **argv)
{

    return 0;
}