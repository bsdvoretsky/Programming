#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    if (a >= b) return a;
    return b;
}

int overlap(char *s1, char *s2) 
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    if (l1 * l2 == 0) {
        return 0;
    }

    for (int i = 0; i < l1; i++) {
        if (s1[i] != s2[i]) {
            return overlap(s1 + 1, s2);
        }
    }

    return l1;
}

int superstr(char **strs, int length)
{
    int l_o = 0;

    for (int i = 0; i < length; i++) {
        l_o += strlen(strs[i]);
    }

    int arr[length * length];
    int m, x_m, y_m;
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < length; x++) {
            if (x == y) {
                arr[y * length + x] = 0;
            }
            else {
                arr[y * length + x] = overlap(strs[y], strs[x]);
            }
        }
    }

    for (int k = 0; k < length - 1; k++) {
        m = 0, x_m = 0, y_m = 0;

        for (int y = 0; y < length; y++) {
            for (int x = 0; x < length; x++) {
                if (m < arr[y * length + x]) {
                    m = arr[y * length + x];
                    x_m = x;
                    y_m = y;
                }
            }
        }

        if (m == 0) {
            return l_o;
        }
        else {
            l_o -= m;
            for (int y = 0; y < length; y++) {
                for (int x = 0; x < length; x++) {
                    if (y == y_m || x == x_m) {
                        arr[y * length + x] = 0;
                    }
                }
            }
        }
    }

    return l_o;
}

int main (int argc, char **argv)
{
    int n;
    scanf("%d\n", &n);
    char *strs[n];
    for (int i = 0; i < n; i++) {
        strs[i] = calloc (4096, sizeof(char));
        gets(strs[i]);
    }
    printf("%d\n", superstr(strs, n));
    return 0;
}

