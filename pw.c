#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORDCOUNT 3
#define DIGITCOUNT 2
#define DICTPATH "/usr/share/dict/words"
#define MAXLEN 64

enum { FALSE, TRUE };

int dict_len(const char *dictname);
char *get_random_word(int max, const char *dictname);
void map(int (*f)(int), char *str, int len);

int
dict_len(const char *dictname)
{
	int words = 0;
	char c;
	FILE *dict = fopen(dictname, "r");

	while ((c = getc(dict)) != EOF)
		if (isspace(c))
			words++;
	fclose(dict);
	return words;
}

char 
*get_random_word(int max, const char *dictname)
{
	FILE *dict = fopen(dictname, "r");
	int target_index, current_index = 0, i;
	char c, *word = malloc(sizeof(char) * MAXLEN);

	if (word == NULL) {
		printf("Malloc error\n");
		exit(-1);
	}
	if (max < RAND_MAX)
		target_index = rand() % max;
	else {
		target_index = 0;
		for (i = 0; i < (max / RAND_MAX); i++)
			target_index += rand();
	}
	while (current_index < target_index) {
		c = getc(dict);
		while (isspace(c) == FALSE)
			c = getc(dict);
		current_index++;
	}
	fscanf(dict, "%s\n", word);
	fclose(dict);
	return word;
}

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
