#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long sarr_l(char **s, int n) {
  unsigned long len = 0;
  for (int i = 0; i < n; i++) {
    len += strlen(s[i]);
  }
  return len;
}

char *concat(char **s, int n) {
  char *res = malloc(sarr_l(s, n) + 1);
  unsigned long l = 0;
  for (int i = 0; i < n; i++) {
			memcpy(res + l, s[i], strlen(s[i]));
			l += strlen(s[i]);
    }
	memcpy(res + sarr_l(s, n), "\0", 1);
  return res;
  }

size_t fib_len(int n) 
{
    if (n == 1 || n == 2) {
        return 1;
    }
    else {
        return (fib_len(n - 1) + fib_len(n - 2));
    }
}

char *fibstr(int n)
{
    if (n == 1) {
        char *s = malloc(2);
        memcpy(s, "a", 1);
        memcpy(s + 1, "\0", 1);
        return s;
    }
    else if (n == 2) {
        char *s = malloc(2);
        memcpy(s, "b", 1);
        memcpy(s + 1, "\0", 1);
        return s;
    }
    else {
        char *s[2] = {fibstr(n - 2), fibstr(n - 1)};
        return concat(s, 2);
    }
}

int main(int argc, char **argv)
{   
    int n;
    printf("Input n:\n");
    scanf("%d", &n);
    printf("%s\n", fibstr(n));
    return 0;
}