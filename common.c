#include "common.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	return words+1;
}

char 
*get_random_word(int max, const char *dictname)
{
	FILE *dict = fopen(dictname, "r");
	int target_index, current_index = 0, i, valid = FALSE, looped = FALSE;
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
	while (valid == FALSE) {
		valid = TRUE;
		fscanf(dict, "%s\n", word);
		current_index++;
		if (current_index == max) {
			if (looped) {
				printf("All words contain non alpha chars\n");
				free(word);
				fclose(dict);
				exit(1);
			}
			current_index = 0;
			rewind(dict);
			looped = TRUE;
		}
		for (i = 0; i < strlen(word); i++) {
			if (isalpha(word[i]) == FALSE) {
				valid = FALSE;
				break;
			} else {
				word[i] = tolower(word[i]);
			}
		}
	}
	fclose(dict);
	return word;
}
