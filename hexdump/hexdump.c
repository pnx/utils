/* hexdump.c
 *
 *  Copyright (C) 2013   Henrik Hautakoski <henrik@fiktivkod.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include "hexdump.h"

void hexdump(unsigned char *ptr, unsigned size) {

	int i;

	/* Header */
	printf("   Address                           Data\n");
	printf("-------------  -----------------------------------------------\n");

	/* print 16 bytes per line.*/
	for(i=0; i < size; i++) {

		int c = i % 16;

		/* print address. */
		if (c == 0)
			printf("%4i %.8X: ", i, i);

		printf("%.2X ", *(ptr + i));

		/* 16:th byte in the row, jump to new line.*/
		if (c == 15)
			printf("\n");
	}

	/* print an newline if we exited in the middle of a row */
	if (size % 16)
		printf("\n");
}
