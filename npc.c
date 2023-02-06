/*
Copyright 2023 Ray Garner

This program is free software: you can redistribute it and/or modify it under 
the terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
	printf("Invalid class. Choose (f)ighter, (c)leric, (m)agic-user or "\
	       "(t)hief\n");
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

	if (argc < 3) {
		printf("Please pass class and level as args\n");
		printf("eg: npc f 5\n");
		return 1;
	}
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
