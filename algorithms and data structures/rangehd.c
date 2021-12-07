#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
	int m, l, r, i, t, fl;
	int alphabet[26];
	char *a = calloc(1000000, sizeof(char)), op[4], 
	*s = calloc(1000000, sizeof(char));
	gets(a);
	scanf("%d", &m);

	for (int j = 0; j < m; ++j) {
		scanf("%s", op);
		if (!strcmp(op, "HD")) {
			for (int j = 0; j < 26; ++j) {
				alphabet[j] = 0;
			}
			fl = 0;
			scanf("%d %d", &l, &r);
			for (int k = l; k <= r; ++k) {
				alphabet[(int) a[k] - 97]++;
			}
			if ((r - l) % 2 == 1) {
				for (int k = 0; k < 26; ++k) {
					if (alphabet[k] % 2 == 1) {
						fl = 1;
						break;
					}
				}
			}
			else {
				t = 0;
				for (int k = 0; k < 26; ++k) {
					if (alphabet[k] % 2 == 1) {
						t++;
						if (t == 2) {
							fl = 1;
							break;
						}
					} 
				}
			}
			if (fl == 1) printf("NO\n");
			else printf("YES\n");
		}
		else if (!strcmp(op, "UPD")) {
			scanf("%d %s", &i, s);
			for (int k = i; k < i + strlen(s); ++k) {
				a[k] = (char) s[k - i];
			}
		}
	}
	free(a);
	free(s);
	return 0;
}