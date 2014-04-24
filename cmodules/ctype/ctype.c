/*
 * ctype.c - Locale independant ctype.
 *
 *  Copyright (C) 2012-2013   Henrik Hautakoski <henrik@fiktivkod.org>
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
#include "ctype.h"

enum {
	S = CTYPE_MASK_SPACE,
	L = CTYPE_MASK_LOWER,
	U = CTYPE_MASK_UPPER,
	D = CTYPE_MASK_DIGIT
};

unsigned char __ctype_table[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, S, S, 0, 0, S, 0, 0,	/* 00-0F */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* 10-1F */
	S, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* 20-2F */
	D, D, D, D, D, D, D, D, D, D, 0, 0, 0, 0, 0, 0,	/* 30-3F */
	0, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,	/* 40-4F */
	U, U, U, U, U, U, U, U, U, U, U, 0, 0, 0, 0, 0,	/* 50-5F */
	0, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L,	/* 60-6F */
	L, L, L, L, L, L, L, L, L, L, L, 0, 0, 0, 0, 0,	/* 70-7F */
};
