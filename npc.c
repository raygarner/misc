/* npc generator */
/* npc <class> <level> */
/* classes: fighter, cleric, thief, magic-user */
/* level: 1-20 */
/* eg: npc fighter 5 */
/* first character works for class: npc f 5 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLASSES 4
#define RACES 4
#define REQ_LIMIT 9
#define ABILITIES 6
#define MAX_LEVEL 20

enum { DWARF, ELF, HALFLING, HUMAN };

enum { FIGHTER, CLERIC, THIEF, MAGIC_USER };

enum { STR, INT, WIS, DEX, CON, CHA };

const int race_req[RACES] = {CON, INT, DEX, -1};
const int class_req[CLASSES] = {STR, WIS, DEX, INT};
const char *race_str[RACES] = {"dwarf", "elf", "halfling", "human"};
const char *class_str[CLASSES] = {"fighter", "cleric", "thief", "magic-user"};
const char *ability_str[ABILITIES] = {"STR", "INT", "WIS", "DEX", "CON", "CHA"};
const int modifier[16] = {-3,-2,-2,-1,-1,-1,0,0,0,0,1,1,1,2,2,3};

int read_class(char);
int hd_size(int, int);
int roll(int, int);
int gen_race(int);
char *format_modifier(int);

int
read_class(char class)
{
	switch (class) {
	case 'f':
		return FIGHTER;
	case 'c':
		return CLERIC;
	case 't':
		return THIEF;
	case 'm':
		return MAGIC_USER;
	}
	printf("Invalid class. Choose fighter, cleric, magic-user or "\
	       "thief\n");
	exit(-1);
}

int
hd_size(int race, int class)
{
	switch (class) {
	case FIGHTER:
		return (race == HALFLING || race == ELF) ? 6 : 8;
	case CLERIC:
		return 6;
	case THIEF:
		return 4;
	case MAGIC_USER:
		return 4;
	default:
		return -1;
	}
	printf("Invalid class to generate HD size for\n");
	exit(-1);
}

int
roll(int count, int sides)
{
	int i, total = 0;

	for (i = 0; i < count; i++)
		total += (rand() % (sides)) + 1;
	return total;
}

int
gen_race(int class)
{
	switch (class) {
	case FIGHTER: /* fallthrough */
	case CLERIC:  /* fallthrough */
	case THIEF:   /* fallthrough */
		return rand() % 4;
	case MAGIC_USER:
		return rand() % 2 == 0 ? HUMAN : ELF;
	}
	printf("Invalid class to generate race for\n");
	exit(-1);
}

char *
format_modifier(int m)
{
	char *str = calloc(6, sizeof(char));
	int start = 1;

	str[0] = '(';
	if (m >= 0) {
		str[1] = '+';
		start++;
	}
	sprintf(&str[start], "%d)", m);
	return str;
}

int
main(int argc, char *argv[])
{
	int class, level, race, abilities[ABILITIES], hp = 0, a, hd;
	char *mod;

	srand(time(NULL));
	class = argc > 1 ? read_class(tolower(argv[1][0])) : rand() % CLASSES;
	level = argc > 2 ? atoi(argv[2]) : rand() % MAX_LEVEL + 1;
	race = gen_race(class);
	if (level > MAX_LEVEL || level < 1) {
		printf("Invalid level. Level must be between 1 and 20\n");
		return -1;
	}
	printf("Level %d %s %s\n", level, race_str[race], \
	    class_str[class]);
	for (a = 0; a < ABILITIES; a++) {
		abilities[a] = roll(3, 6);
		while (abilities[a] < REQ_LIMIT && \
		    (a == class_req[class] || a == race_req[race]))
			abilities[a] = roll(3, 6);
		mod = format_modifier(modifier[abilities[a] - 3]);
		printf("%s: %2d %s\n", ability_str[a], abilities[a], mod);
		free(mod);
	}
	hd = hd_size(race, class);
	for (a = 0; a < level; a++)
		hp += roll(1, hd) + modifier[abilities[CON]-3];
	printf("HP: %3d\n", hp);
	return 0;
}
