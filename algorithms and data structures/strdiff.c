#include <stdio.h>
#include <string.h>

void revarray(void* base, size_t nel, size_t width)
{
    for (size_t i = 0, j = (nel - 1) * width; i < j; i += width, j -= width)
        for (size_t k = 0; k < width; k++) {
            *(((char*) base) + i + k) ^= *(((char*) base) + j + k);
            *(((char*) base) + j + k) ^= *(((char*) base) + i + k);
            *(((char*) base) + i + k) ^= *(((char*) base) + j + k);
        }
}

void binstr(char *s, int *arr, size_t size) {
    size_t l = size / 8 - 1;
    for (size_t i = 0; i < l; i++) {
        for (int j = 0; j < 8; j++) {
            if (*(s + i) & 1 << j) *(arr + 8 * i + j) = 1;
            else *(arr + 8 * i + j) = 0;
        }
    }
    for (int i = 0; i < 8; i++) 
        *(arr + size - 8 + i) = 0;
    revarray(arr, size, sizeof(int));
}

int strdiff(char *a, char *b)
{   
    size_t l1 = (strlen(a) + 1) * 8;
    size_t l2 = (strlen(b) + 1) * 8;
    size_t l;
    if (l1 >= l2) l = l1;
    else l = l2;
    int a_r[l];
    int b_r[l];
    binstr(a, a_r, l);
    binstr(b, b_r, l);

    for (size_t i = 0; i < (l / 8); i++) {
        for (int j = 0; j < 8; j++) {
            if (a_r[l - 8 * (i + 1) + j] !=
            b_r[l - 8 * (i + 1) + j]) {
                return 8 * i + j - 1;
            }
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    char *a = "lo";
    char *b = "ll";
    printf("%d", strdiff(a, b));
    return 0;
}