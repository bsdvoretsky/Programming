#include <stdio.h>

void minarr (int* p, int size, int* r) {
    int min = p[0], x = 0;
    for (int i = 0; i < size; i++) {
        if (p[i] < min) {
            min = p[i];
            x = i;
        }
    }
    r[0] = min;
    r[1] = x;
}

void maxarr (int* p, int size, int* r) {
    int max = p[0], y = 0;
    for (int i = 0; i  < size; i++) {
        if (p[i] > max) {
            max = p[i];
            y = i;
        }
    }
    r[0] = max;
    r[1] = y;
}

int main(int argc, char **argv)
{
    int m, n, t;
    scanf("%d %d", &m, &n);
    int maxrow[m], mincol[n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &t);
            if ((i == 0) && (j == 0)) {
                maxrow[i] = t;
                mincol[j] = t;
            }
            else if (i == 0) {
                mincol[j] = t;
                if (t > maxrow[i]) {
                    maxrow[i] = t;
                }
            }
            else if (j == 0) {
                maxrow[i] = t;
                if (t < mincol[j]) {
                    mincol[j] = t;
                }
            }
            else {
                if (t > maxrow[i]) {
                    maxrow[i] = t;
                }
                if (t < mincol[j]) {
                    mincol[j] = t;
                }
            }
        }
    }
    int ma[2] = {0, 0};
    int mi[2] = {0, 0};
    minarr(maxrow, m, mi);
    maxarr(mincol, n, ma);
    if (ma[0] == mi[0]) {
        printf("%d %d\n", mi[1], ma[1]);
    }
    else {
        printf("none\n");
    }
    return 0;
}