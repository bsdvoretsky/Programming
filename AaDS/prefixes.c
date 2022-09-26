#include <stdio.h>
#include <string.h>

size_t prefix(char *str, size_t i, size_t k, size_t length, size_t prefix_arr[length]) {
	if (str[i] == str[k]) return k + 1;
	if (k == 0) return 0;
	prefix(str, i, prefix_arr[k - 1], length, prefix_arr);
}

void prefixes(char *str, size_t length) {
	size_t prefix_arr[length];
	size_t t;
	prefix_arr[0] = 0;
	for (size_t i = 1; i < length; ++i)
		prefix_arr[i] = prefix(str, i, prefix_arr[i - 1], length, prefix_arr);
	for (size_t i = 2; i < length + 1; ++i) {
		t = prefix_arr[i - 1];
		while (t >= i / 2) {
			if (i % (i - t) == 0) {
				printf("%lu %lu\n", i, i / (i - t));
			}
			if (t == i / 2) break;
			t = prefix_arr[t - 1];
		}
	}
}

int main(int argc, char **argv) {
	char *a = argv[1];
	prefixes(a, strlen(a));
	return 0;
}