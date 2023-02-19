#include "common.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int
dict_len(const char *dictname)
{
	int words = 0;
	char c;
	FILE *dict = fopen(dictname, "r");

	while ((c = getc(dict)) != EOF)
		if (c == SEPARATE)
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
