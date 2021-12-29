#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void csort(char *src, char *dest)
{
    char *a[5000];
    int a_n[5000];
    for (int i = 0; i < 5000; ++i) {
        a[i] = (char *) calloc(5000, sizeof(char));
        a_n[i] = 0;
    }
    int b = -1, e, fl = 0;
    for (int i = 0; i < strlen(src); ++i) {
        if (src[i] != ' ' && fl == 0) {
            b = i;
            fl = 1;
        } 
        else if (src[i] == ' ') {
            e = i;
            if (b >= 0 && fl == 1) {
                if (a_n[e-b] > 0) {
                    strcpy(a[e-b] + strlen(a[e-b]), " ");
                }
                strncpy(a[e-b] + strlen(a[e-b]), src + b, e-b);
                a_n[e-b]++;
                fl = 0;
            }
        }
    }
    e = strlen(src);
    if (b >= 0) {
        if (a_n[e-b] > 0) {
            strcpy(a[e-b] + strlen(a[e-b]), " ");
        }
        strncpy(a[e-b] + strlen(a[e-b]), src + b, e-b);
        a_n[e-b]++;
    }

    for (int i = 0; i < 5000; i++) {
        if (a_n[i] != 0) {
            strcpy(dest + strlen(dest), a[i]);
            strcpy(dest + strlen(dest), " ");
        }
    }
    for (int i = 0; i < 5000; ++i) {
        free(a[i]);
    }
}

int main(int argc, char **argv)
{
    char *src = (char *) calloc(5000, sizeof(char));
    char *dest = (char *) calloc(5000, sizeof(char));
    gets(src);
    csort(src, dest);
    printf("%s", dest);
    free(src);
    free(dest);
    return 0;
}