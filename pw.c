#include "common.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORDCOUNT 3
#define DIGITCOUNT 2
#define MAXLEN 64

int dict_len(const char *dictname);
char *get_random_word(int max, const char *dictname);
void map(int (*f)(int), char *str, int len);

void
map(int (*f)(int), char *str, int len)
{
	int i;

	for (i = 0; i < len; i++)
		str[i] = f(str[i]);
}

int
main(int argc, char *argv[])
{
	char dictpath[MAXLEN], pass[MAXLEN], *tmp;
	int i, n = 0, len, wordlen, r;
	FILE *f;

	if (argc < 2) {
		printf("Please pass dictionary file as arg\n");
		printf("eg: pw words.txt\n");
		return 1;
	} else
		strcpy(dictpath, argv[1]);
	f = fopen(dictpath, "r");
	if (f == NULL) {
		printf("Dictionary not found\n");
		return -1;
	}
	fclose(f);
	len = dict_len(dictpath);
	srand(time(NULL));
	for (i = 0; i < WORDCOUNT; i++) {
		tmp = get_random_word(len, dictpath);
		wordlen = strlen(tmp);
		if (i == WORDCOUNT - 1)
			map(toupper, tmp, wordlen);
		else
			map(tolower, tmp, wordlen);
		strcpy(&pass[n], tmp);
		n += wordlen;
		pass[n++] = '!';
		free(tmp);
	}
	for (i = 0; i < DIGITCOUNT; i++) {
		r = rand() % 10;
		pass[n++] = r + '0';
	}
	printf("%s\n", pass);
	return 0;
}
