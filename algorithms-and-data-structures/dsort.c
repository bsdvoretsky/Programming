#include <stdio.h>
#include <string.h>

void dsort(char *src)
{
	long alphabet[26];

	for (int i = 0; i < 26; i++) {
		alphabet[i] = 0;
	}

	size_t length = strlen(src);

	for (long i = 0; i < length; i++) {
		++alphabet[((int) src[i]) - 97];
	}

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < alphabet[i]; j++) {
			printf("%c", (char) (i + 97));
		}
	}

	printf("\n");
}


int main (int argc, char **argv)
{
	char src[2000000];
	gets(src);
	dsort(src);
	return 0;
}