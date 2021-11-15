#include <stdio.h>
#include <string.h>

void dsort(char *src)
{
	long alphabet[26];

	for (int i = 0; i < 26; i++) {
		alphabet[i] = 0;
	}

	for (long i = 0; i < strlen(src); i++) {
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
	char src[1000000];
	gets(src);
	dsort(src);
	return 0;
}