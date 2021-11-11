#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int atoi(const char *str);

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("Usage: frame <height> <width> <text>\n");
    }
    else {
        int h = atoi(argv[1]);
        int w = atoi(argv[2]);
        char *s = argv[3];
        size_t l = strlen(s);
    
        if (l >= w - 1 || h <= 3) {
            printf("Error\n");
        } 
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (y == 0 || y == h - 1 || x == 0 || x == w - 1) {
                        printf("*");
                    }
                    else if (y == (h - 1) / 2 && x >= (w - l) / 2 && x <= (w + l) / 2 - 1) {
                        printf("%c", s[x - (w - l) / 2]);
                    }
                    else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}