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

#define WIDTH 32
#define POINTS 3
#define DISPLAYWIDTH WIDTH+POINTS
#define OCTETS 4
#define OCTETLEN 4
#define FALSE 0

enum {
	INVALID_CLASS = '?',
	A_CLASS = 'A',
	B_CLASS = 'B',
	C_CLASS = 'C'
};


int get_octet(int, int);
int is_mask_valid_for_class(char, int);
char network_class(int);
int build_mask_from_width(int);
int parse_octet(const char *, int *);
int parse_ip(const char *, int *);
void ip_to_str(int, char *);

int
get_octet(int o, int address)
{
	if (o < 1 || o > 4)
		return -1;
	return (address & (0xff000000 >> (8 * (o - 1)))) >> (8 * (4 - o));
}

int
is_mask_valid_for_class(char class, int mask)
{
	switch (class) {
	case A_CLASS:
		return mask >= 0xff000000;
	case B_CLASS:
		return mask >= 0xffff0000;
	case C_CLASS:
		return mask >= 0xffffff00;
	default:
		return FALSE;
	}
}

char
network_class(int address)
{
	int first_octet = (address & 0xff000000) >> (8 * 3);

	if (first_octet < 127)
		return A_CLASS;
	if (first_octet < 192)
		return B_CLASS;
	if (first_octet < 223)
		return C_CLASS;
	return INVALID_CLASS;
}

int
build_mask_from_width(int width)
{
	int i, mask = 0;

	for (i = 0; i < width; i++)
		mask |= 0x80000000 >> i; /* flip 1 more bit */
	return mask;
}

int
parse_octet(const char *start, int *octet)
{
	char octetstr[OCTETLEN] = "\0";
	int i = -1;

	while (isdigit(start[++i]))
		octetstr[i] = start[i];
	*octet = atoi(octetstr); /* return len */
	return i+1;
}

int
parse_ip(const char *ip, int *address)
{
	int i, octet, len = *address = 0;

	for (i = 0; i < 4; i++) {
		len += parse_octet(&ip[len], &octet);
		*address |= octet << 8 * (3 - i);
	}
	return atoi(&ip[len]); /* return mask width */
}

void
ip_to_str(int ip, char *str)
{
	sprintf(str, "%d.%d.%d.%d", get_octet(1, ip), get_octet(2, ip),
	                            get_octet(3, ip), get_octet(4, ip));
}

int
main(int argc, char *argv[])
{
	int mask_width, address, mask;
	char ipstr[DISPLAYWIDTH];

	if (argc < 2) {
		printf("Please supply a CIDR IP as an arg\n");
		printf("eg: ipc 192.168.0.1/24\n");
		return 1;
	} else {
		mask_width = parse_ip(argv[1], &address);
	}
	mask = build_mask_from_width(mask_width);
	if (!is_mask_valid_for_class(network_class(address), mask)) {
		printf("invalid netmask for network class %c\n", 
		       network_class(address));
		return 0;
	}
	ip_to_str(address, ipstr);
	printf("Address:\t\t%s\n", ipstr);
	ip_to_str(mask, ipstr);
	printf("Subnet mask:\t\t%s\n", ipstr);
	ip_to_str(address & mask, ipstr);
	printf("Subnet ID:\t\t%s\n", ipstr);
	ip_to_str(address | ~mask, ipstr);
	printf("Broadcast address:\t%s\n", ipstr);
	ip_to_str(address & (mask + 1), ipstr);
	printf("Host IP Range:\t\t%s -> ", ipstr);
	ip_to_str((address | ~mask) - 1, ipstr);
	printf("%s\n", ipstr);
	printf("Hosts per subnet:\t%d\n", ~mask - 1);
	return 0;
}
