#include <stdio.h>
#include <string.h>

int min (int a, int b) {
	if (a <= b) return a;
	return b;
}

int max (int a, int b) {
	if (a >= b) return a;
	return b;
}

void bmall(char *a, char *b, int *stop_symbols, int *suffshift) {
	int t = 0, last = strlen(a) - 1, p;
	while (t < strlen(b) - last) {
		p = last;
		while ((p >= 0) && (b[t + p] == a[p])) p--;
		if (p == -1) {
			printf("%d\n", t);
			t += last + 1;
		}
		else {
			t += max(suffshift[p + 1], p - stop_symbols[(int) b[t + p] - 97]);
		}
	}
}


int main(int argc, char **argv)
{
	char *s = argv[1], *t = argv[2];
	int stop_symbols[26];
	for (int i = 0; i < 26; ++i) {
		stop_symbols[i] = -1;
		for (int j = strlen(s) - 2; j >= 0; j--) {
			if ((s[j] == (char) (i + 97)) && (stop_symbols[i] == -1)) stop_symbols[i] = j;
		}
	}
	int m = strlen(s);
	int suffshift[m + 1];
	for (int i = 0; i < m + 1; ++i) {
		suffshift[i] = m;
	}
	int z[m];
	for (int i = 0; i < m; ++i) {
		z[i] = 0;
	}
	for (int j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) {
   		if (j <= maxZ) z[j] = min(maxZ - j + 1, z[j - maxZidx]);
   		while (j + z[j] < m && s[m - 1 - z[j]] == s[m - 1 - (j + z[j])]) z[j]++;
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
 	}
	for (int j = m - 1; j > 0; j--) suffshift[m - z[j]] = j;
	for (int j = 1, r = 0; j <= m - 1; j++) {
	    if (j + z[j] == m) {
	    	for (; r <= j; r++) {
	       		if (suffshift[r] == m) suffshift[r] = j;
	    	}
	    }
	}

	bmall(s, t, stop_symbols, suffshift);
	return 0;
}