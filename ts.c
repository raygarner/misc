#include "common.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 16
#define DICTNAME "/usr/share/dict/words"

double calc_cpm(int chars, double seconds);
double calc_wpm(double cpm, double avglen);
int dict_len(const char *dictname);
char *get_random_word(int max, const char *dictname);

double
calc_cpm(int chars, double seconds)
{
	return (chars / seconds) * 60;
}

double
calc_wpm(double cpm, double avglen)
{
	return cpm / avglen;
}

int
main(int argc, char *argv[])
{
	int wc = MAXWORDS, i, totalchars = 0, correctwords = 0;
	char *word, input[MAXLEN], dictname[MAXLEN] = DICTNAME;
	time_t start_time, end_time;
	FILE *f;
	double totalseconds, cpm, wpm, avglen;

	if (argc < 3) {
		printf("Please pass wordcount and dictionary file as args\n");
		printf("eg: ts 8 words.txt\n");
		return 1;
	} else {
		wc = atoi(argv[1]);
		if (wc < 1) {
			printf("Invalid word count\n");
			printf("Please pass wordcount and dictionary file as args\n");
			printf("eg: ts 8 words.txt\n");
			return 1;
		}
		
		if ((f = fopen(argv[2], "r")) == NULL) {
			printf("Dictionary '%s' does not exist\n", argv[2]);
			return 1;
		} else {
			strcpy(dictname, argv[2]);
			fclose(f);
		}
	}
	srand(time(NULL));
	start_time = time(NULL);
	for (i = 0; i < wc; i++) {
		word = get_random_word(dict_len(dictname), dictname);
		printf("word: %s\n", word);
		printf("type: ");
		scanf("%s", input);
		if (strcmp(input, word) == 0) {
			printf("correct\n");
			totalchars += strlen(word);
			correctwords++;
		} else {
			printf("incorrect\n");
		}
		free(word);
		putchar('\n');
	}
	end_time = time(NULL);
	totalseconds = difftime(end_time, start_time);
	avglen = (double) totalchars / (double) correctwords;
	printf("average word length = %f\n", avglen);
	cpm = calc_cpm(totalchars, totalseconds);
	wpm = calc_wpm(cpm, avglen);
	printf("totalseconds = %d\n", totalseconds);
	printf("cpm = %f\n", cpm);
	printf("totalchars = %d\n", totalchars);
	printf("%f wpm\n", wpm);
	return 0;
}
