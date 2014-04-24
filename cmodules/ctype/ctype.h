/*
 * ctype.h - Locale independant ctype.
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
#ifndef CTYPE_H
#define CTYPE_H

extern unsigned char __ctype_table[256];

#define __ctype_test(x, m) ((__ctype_table[(unsigned char)(x)] & (m)) != 0)

#define CTYPE_MASK_SPACE (1<<0)
#define CTYPE_MASK_LOWER (1<<1)
#define CTYPE_MASK_UPPER (1<<2)
#define CTYPE_MASK_DIGIT (1<<3)

#define isupper(x) __ctype_test(x, CTYPE_MASK_UPPER)
#define islower(x) __ctype_test(x, CTYPE_MASK_LOWER)
#define isalpha(x) __ctype_test(x, CTYPE_MASK_LOWER | CTYPE_MASK_UPPER)

#define isalnum(x) \
	__ctype_test(x, CTYPE_MASK_LOWER | CTYPE_MASK_UPPER | CTYPE_MASK_DIGIT)

#define isdigit(x) __ctype_test(x, CTYPE_MASK_DIGIT)
#define isspace(x) __ctype_test(x, CTYPE_MASK_SPACE)

static inline int toupper(int c) {

	return islower(c) ? c + 0x20 : c;
}

static inline int tolower(int c) {

	return isupper(c) ? c - 0x20 : c;
}

#endif /* CTYPE_H */
