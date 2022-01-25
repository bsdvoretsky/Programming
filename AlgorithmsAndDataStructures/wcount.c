#include <stdio.h>
#include <string.h>

int wcount(char *s)
{
    int flag = 1;
    int res = 0;
    for (size_t i = 0; i < strlen(s); ++i) {
        if (s[i] != ' ' && flag) {
            ++res;
            flag = 0;
        }
        else if (s[i] == ' ') flag = 1;
    }

    return res;
}

int main (int argc, char **argv)
{
    char *s = "  1  2  34  6_2  hello 56  _  "; // 7
    printf("%d", wcount(s));
    return 0;
}