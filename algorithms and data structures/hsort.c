#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (const void *a, const void *b) {
	size_t l1 = 0, l2 = 0, i = 0;
	while (*(char *)(a + i) != '\0') {
		if (*(char *)(a + i) == 'a') {
			l1++;
		}
		i++;
	}
	i = 0;
	while (*(char *)(b + i) != '\0') {
		if (*(char *)(b + i) == 'a') {
			l2++;
		}
		i++;
	}
	if (l1 < l2) return -1;
	else if (l1 == l2) return 0;
	return 1;
}

void hsort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b))
{
	if (nel != 1 && nel != 2) {
		void *root, *child1, *child2;
		root = calloc(1, width);
		child1 = calloc(1, width);
		child2 = calloc(1, width);
		for (size_t k = 0; k < nel / 2 + 1; k++) {
			for (size_t i = 0; i < nel * width / 2; i+=width) {
				for (int j = 0; j < width; j++) {
					*(char *) (root + j) = *(char *) (base + i + j);
				}
				if (2 * i + width < nel * width) {
					for (int j = 0; j < width; j++) {
						*(char *) (child1 + j) = *(char *) (base + 2 * i + width + j);
					}
					if (2 * i + 2 * width < nel * width) {
						for (int j = 0; j < width; j++) {
							*(char *) (child2 + j) = *(char *) (base + 2 * (i + width) + j);
						}
						if (compare(child1, child2) != -1 && compare(root, child1) == -1) {
							for (int j = 0; j < width; j++) {
								*((char *) (base + i + j)) = *((char *) (child1 + j));
								*((char *) (base + 2 * i + width + j)) = *((char *) (root + j));
							}
						}
						else if (compare(child2, child1) != -1 && compare(root, child2) == -1) {
							for (int j = 0; j < width; j++) {
								*((char *) (base + i + j)) = *((char *) (child2 + j));
								*((char *) (base + 2 * i + 2 * width + j)) = *((char *) (root + j));
							}
						}
					}
					else {
						if (compare(root, child1) == -1) {
							for (int j = 0; j < width; j++) {
								*((char *) (base + i + j)) = *((char *) (child1 + j));
								*((char *) (base + 2 * i + width + j)) = *((char *) (root + j));
							}
						}
					}
				}
			}
		}
		for (int j = 0; j < width; j++) {
			*(char *) (root + j) = *(char *) (base + j);
			*(char *) (base + j) = *(char *) (base + (nel - 1) * width + j);
			*(char *) (base + (nel - 1) * width + j) = *(char *) (root + j);
		}
		free(root);
		free(child1);
		free(child2);
		hsort(base, nel - 1, width, compare);
	} 
	else if (nel == 2) {
		char temp;
		if (compare(base + width, base) == -1) {
			for (int i = 0; i < width; ++i) {
				temp = *((char *) base + i);
				*((char *) base + i) = *((char *) (base + width + i));
				*((char *) (base + width + i)) = temp;
			}
		}
	}
}

int main(int argc, char **argv)
{
	int n;
	scanf("%d", &n);
	char a[n][5000];
	for (int i = 0; i < n; ++i) {
		scanf("%s", a[i]);
	}
	hsort(a, n, sizeof(char) * 5000, compare);
	for (int i = 0; i < n; ++i) {
		printf("%s ", a[i]);
	}
	return 0;
}