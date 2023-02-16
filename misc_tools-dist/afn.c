#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define OFFSET '!'
#define MAX    '~'
#define SYMBOLS MAX - OFFSET + 1

enum {
	ENCRYPT,
	DECRYPT
};

int gen_multiplier();
int clock_mod(int, int);
char encrypt(char, int, int);
int ext_euc(int, int, int *, int *);
char decrypt(char, int, int);
void apply(int, int, int, FILE *);

int
gen_multiplier()
{
	int a = rand() % SYMBOLS, x, y;

	while (ext_euc(a, SYMBOLS, &x, &y) != 1)
		a = rand() % SYMBOLS;
	return a;
}

int
clock_mod(int x, int m)
{
	return x < 0 ? m - (abs(x) % m) : x % m;
}

char
encrypt(char c, int a, int b)
{
	return clock_mod(a*c+b, SYMBOLS);
}

/* ax + by = gcd(a, b) */
/* x is the modular multiplicative inverse of a in modulus b */
/* returns gcd(a, b) */
/* wikipedia 'extended euclidean algorithm' */
int
ext_euc(int a, int b, int *x, int *y)
{
	int q, tmp;
	int old_r = a, r = b;
	int old_s = 1, s = 0;
	int old_t = 0, t = 1;

	while (r != 0) {
		q = old_r / r; /* euc div */
		tmp = old_r;
		old_r = r;
		r = tmp - q * r;
		tmp = old_s;
		old_s = s;
		s = tmp - q * s;
		tmp = old_t;
		old_t = t;
		t = tmp - q * t;
	}
	*x = old_s;
	*y = old_t;
	return old_r;
}

char
decrypt(char c, int a, int b)
{
	int x, y;

	ext_euc(a, SYMBOLS, &x, &y);
	return clock_mod(x * (c-b), SYMBOLS);
}

void
apply(int a, int b, int mode, FILE *f)
{
	char (*g)(char, int, int), c;

	g = mode == ENCRYPT ? encrypt : decrypt;
	while ((c = getc(f)) != EOF) {
		if (OFFSET <= c && c <= MAX)
			c = g(c-OFFSET, a, b) + OFFSET;
		putchar(c);
	}
}

int
main(int argc, char *argv[])
{
	FILE *f;
	int a, b, k, mode;

	if (argc < 4) {
		printf("Please supply file, mode and key as args\n");
		printf("eg: afn data.txt e 64\n");
		return 1;
	}
	k = atoi(argv[3]);
	if (k == 0) {
		printf("Please supply a number as the key\n");
		printf("eg: afn data.txt e 64\n");
		return 1;
	}
	if (argv[2][0] == 'e')
		mode = ENCRYPT;
	else if (argv[2][0] == 'd')
		mode = DECRYPT;
	else {
		printf("Invalid mode. Use (e)ncrypt or (d)ecrypt\n");
		printf("eg: afn data.txt e 64\n");
		return 1;
	}
	srand(k);
	f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("File not found\n");
		return 1;
	}
	a = gen_multiplier();
	b = rand() % SYMBOLS;
	apply(a, b, mode, f);
	fclose(f);
	return 0;
}