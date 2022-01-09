#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void csort(char *src, char *dest)
{
    int res[1024][1024];
    int c_res[1024] = {0};
    int i = 0, b, e, fl = 0, j;
    for (i = 0; i < 1024; ++i) {
        for (j = 0; j < 1024; j++) {
            res[i][j] = -1;
        }
    }
    i = 0;
    j = 0;
    int k = 0;
    while (src[i] != '\0') {
        if (src[i] != ' ' && fl == 0) {
            b = i;
            fl = 1;
        }
        else if (src[i] == ' ' && fl == 1) {
            e = i;
            fl = 0;
            res[e - b][c_res[e - b]] = b;
            c_res[e - b]++;
        }
        ++i;
    }
    if (fl == 1) {
        e = i;
        fl = 0;
        res[e - b][c_res[e - b]] = b;
        c_res[e - b]++;
    }
    for (i = 0; i < 1024; i++) {
        for (j = 0; j < 1024; j++) {
            if (res[i][j] != -1) {
                for (int c = 0; c < i; ++c) {
                    dest[k] = src[res[i][j] + c];
                    k++;
                }
                dest[k] = ' ';
                k++;
            }
        }
    }
    dest[k - 1] = '\0';
}

int main(int argc, char const *argv[])
{
    char *src = (char *) calloc (1024, sizeof(char));
    char *dest = (char *) calloc (1024, sizeof(char));
    gets(src);
    csort(src, dest);
    puts(dest);
    free(src);
    free(dest);
    return 0;
}