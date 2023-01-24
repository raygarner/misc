/* shows modes on a guitar fretboard */
/* fb <fret of root note on E string> <degree of major scale> */
/* eg for A natural minor: fb 5 6 */

#include <stdio.h>
#include <stdlib.h>

#define DEGREES 7
#define STRINGS 6
#define OCTAVE 12
#define FRETS OCTAVE
#define EMPTY -1

enum { SEMITONE = 1, TONE };

enum { SIXTH, FIFTH, FOURTH, THIRD, SECOND, FIRST };

const int IONIAN[DEGREES] = {TONE, TONE, SEMITONE, TONE, TONE, TONE, SEMITONE};

void init_string(int[FRETS]);
void print_string(int[FRETS]);
void print_fret_nums(int);
void write_string(int[FRETS], int, int);

void
init_string(int string[FRETS])
{
	int f;

	for (f = 0; f < FRETS; f++)
		string[f] = -1;
}

void
print_string(int string[FRETS])
{
	int f, i;

	putchar('|');
	for (i = 0; i < 2; i++ ) {
		for (f = 0; f < FRETS; f++) {
			if (string[f] != EMPTY)
				printf(" %d|", string[f]+1);
			else
				printf("  |");
		}
	}
	putchar('\n');
}

void
print_fret_nums(int max)
{
	int f;
	
	for (f = 1; f <= max; f++)
		printf("%3d", f);
	putchar('\n');
}

void
write_string(int string[FRETS], int start, int m)
{
	int f = (start - 1) % FRETS, d = 0;

	while (string[f] == EMPTY) {
		string[f] = d;
		f = (f + IONIAN[(d + m) % DEGREES]) % FRETS;
		d = (d + 1) % DEGREES;
	}
}

int
main(int argc, char *argv[])
{
	int fretboard[STRINGS][FRETS], s, f, m;

	m = argc < 3 ? 0 : atoi(argv[2]) - 1;
	f = argc < 2 ? 8 : atoi(argv[1]);
	for (s = 0; s < STRINGS; s++)
		init_string(fretboard[s]);
	write_string(fretboard[SIXTH], f+7*0, m);
	write_string(fretboard[FIFTH], f+7*1, m);
	write_string(fretboard[FOURTH], f+7*2, m);
	write_string(fretboard[THIRD], f+7*3, m);
	write_string(fretboard[SECOND], f+7*4+1, m);
	write_string(fretboard[FIRST], f+7*5+1, m);
	for (s = FIRST; s >= SIXTH; s--)
		print_string(fretboard[s]);
	putchar('\n');
	print_fret_nums(FRETS * 2);
	return 0;
}

