#include <stdio.h>

void revarray(void* base, size_t nel, size_t width)
{
    for (size_t i = 0, j = (nel - 1) * width; i < j; i += width, j -= width)
        for (size_t k = 0; k < width; k++) {
            *(((char*) base) + i + k) ^= *(((char*) base) + j + k);
            *(((char*) base) + j + k) ^= *(((char*) base) + i + k);
            *(((char*) base) + i + k) ^= *(((char*) base) + j + k);
        }
}

int main(int argc, char **argv)
{
    long int array[] = {
        1000000000,
        2000000000,
        3000000000,
        4000000000,
        5000000000
    };
    int arrayN[] = {1, 2, 3, 4, 5};
    char arrayS[5] = {'h', 'e', 'l', 'l', '0'};

    revarray(array, 5, sizeof(long int));
    revarray(arrayN, 5, sizeof(int));
    revarray(arrayS, 5, sizeof(char));

    int i;
    for (i = 0; i < 5; i++) {
        printf("%ld ", array[i]);
    }
    printf("\n");
    for (i = 0; i < 5; i++) {
        printf("%d ", arrayN[i]);
    }
    printf("\n");
    for (i = 0; i < 5; i++) {
        printf("%c ", arrayS[i]);
    }
    printf("\n");
    return 0;
}