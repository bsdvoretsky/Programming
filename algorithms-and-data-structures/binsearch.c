#include <stdio.h>

int compare (unsigned long i) {
    if (*(a + i) > b) return 1;
    if (*(a + i) == b) return 0;
    return -1;
}

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long l = 0;
    unsigned long r =  nel - 1;
    unsigned long m = (l + r) / 2;
    while (m != r && m != l) {
        if (compare(m) == 0) return m;
        else if ((compare(m) == 1)) r = m;
        else l = m;
        m = (l + r) / 2;
    }
    if (compare(l) == 0) return l;
    if (compare(r) == 0) return r;
    return nel;
}


int main(int argc, char **argv)
{
    return 0;
}