/* np <month> <year> */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char
rnd_letter(int len)
{
	return 'A' + (rand() % len);
}

int
modifier(int mon)
{
	if (mon < 3)
		return 49;
	else if (mon > 9)
		return 50;
	else
		return 0;
}

int
main(int argc, char *argv[])
{
	int mon, year;

	srand(time(NULL));
	if (argc < 3) {
		printf("Please pass month and year as args\n");
		printf("eg: np 10 22\n");
		return 1;
	}
	mon = atoi(argv[1]);
	year = atoi(argv[2]);
	if (mon > 12 || mon < 1) {
		printf("Invalid month\n");
		return -1;
	}
	if (year > 50 || year < 0) {
		printf("Year must be between 0 and 50\n");
		return -1;
	}
	putchar(rnd_letter(25));
	putchar(rnd_letter(25));
	printf("%02d", year + modifier(mon));
	putchar(' ');
	putchar(rnd_letter(26));
	putchar(rnd_letter(26));
	putchar(rnd_letter(26));
	putchar('\n');
	return 0;
}
