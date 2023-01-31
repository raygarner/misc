/*
Copyright 2023 Ray Garner

This program is free software: you can redistribute it and/or modify it under 
the 
terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 8

enum {
	KING   = 'k',
	QUEEN  = 'q',
	ROOK   = 'r',
	BISHOP = 'b',
	KNIGHT = 'n',
	EMPTY  = 'e'
};

int     search_piece(const char[WIDTH], int, char);
int     random_free_file(const char[WIDTH]);
int     king_file(const char[WIDTH]);
int     bishop_file(const char[WIDTH]);
int     rook_file(const char[WIDTH]);

int
search_piece(const char pieces[WIDTH], int start, char piece)
{
	int f;

	for (f = start; f < WIDTH; f++)
		if (pieces[f] == piece)
			return f;
	return -1;
}

int
random_free_file(const char pieces[WIDTH])
{
	int file = rand() % WIDTH;

	while (pieces[file] != EMPTY)
		file = rand() % WIDTH;
	return file;
}

int
king_file(const char pieces[WIDTH])
{
	int ra = -1, rb = -1, f;

	ra = search_piece(pieces, 0, ROOK);
	rb = search_piece(pieces, ra+1, ROOK);
	f = random_free_file(pieces);
	while (f <= ra || f >= rb)
		f = random_free_file(pieces);
	return f;
}

int
bishop_file(const char pieces[WIDTH])
{
	int f, bfile = -1;

	bfile = search_piece(pieces, 0, BISHOP);
	if (bfile == -1)
		return random_free_file(pieces);
	else {
		f = random_free_file(pieces);
		while (f % 2 == bfile % 2)
			f = random_free_file(pieces);
		return f;
	}
}

int
rook_file(const char pieces[WIDTH])
{
	int f, rfile = -1;

	rfile = search_piece(pieces, 0, ROOK);
	if (rfile == -1)
		return random_free_file(pieces);
	else {
		f = random_free_file(pieces);
		while (abs(rfile - f) < 2)
			f = random_free_file(pieces);
		return f;
	}
}

int
main(int argc, char *argv[])
{
	char pieces[WIDTH];
	int file;

	srand(time(NULL));
	for (file = 0; file < WIDTH; file++)
		pieces[file] = EMPTY;
	pieces[rook_file(pieces)] = ROOK;
	pieces[rook_file(pieces)] = ROOK;
	pieces[king_file(pieces)] = KING;
	pieces[bishop_file(pieces)] = BISHOP;
	pieces[bishop_file(pieces)] = BISHOP;
	pieces[random_free_file(pieces)] = KNIGHT;
	pieces[random_free_file(pieces)] = KNIGHT;
	pieces[random_free_file(pieces)] = QUEEN;
	for (file = 0; file < WIDTH; file++)
		printf("%c ", pieces[file]);
	putchar('\n');
	return 0;
}

