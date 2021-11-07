#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main (int argc, char **argv)
{
	int n;
	scanf("%d\n", &n);
	char *a[n];
	char line[4096];
	for (int i = 0; i < n; i++) {
		gets(line);
		a[i] = strdup(line);
	}
  printf("%s", concat(a, n));
}