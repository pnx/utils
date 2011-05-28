/* mkfile.c - *nix implementation
 *
 *  Copyright (C) 2011   Henrik Hautakoski <henrik@fiktivkod.org>
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
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <libintl.h>

#define	MIN(a, b) ((a) < (b) ? (a) : (b))

#define	BLOCKSIZE	512

#define	MODE (S_ISVTX + S_IRUSR + S_IWUSR)

off_t size = 0;
int verbose = 0, noalloc = 0;

static int error(const char *msg, ...) {

	int rc;
	va_list vl;
	va_start(vl, msg);
	rc = vfprintf(stderr, gettext(msg), vl);
	va_end(vl);
	return rc;
}

static void usage() {

	error("Usage: mkfile [-nv] <size>[g|m|k|b] <name1> [<name2>] ...\n");
	exit(1);
}

static int isnumeric(const char *str) {

	while(*str)
		if (!isdigit(*str++))
			return 0;
	return 1;
}

static off_t parse_size(char *str) {

	unsigned int factor = 1;
	int len = strlen(str);

	if (len && isalpha(str[len-1])) {

		switch(str[len-1]) {
		case 'b' : case 'B' :
			factor = BLOCKSIZE;
			break;
		case 'k' : case 'K' :
			factor = 1024;
			break;
		case 'm' : case 'M' :
			factor = 1024 * 1024;
			break;
		case 'g' : case 'G' :
			factor = 1024 * 1024 * 1024;
			break;
		default :
			error("unknown size %s\n", str);
			usage();
		}
		str[len-1] = '\0';

		if (!isnumeric(str)) {
			error("unknown size %s\n", str);
			usage();
		}
	}
	return ((off_t)atoll(str) * (off_t)factor);
}

static int mkfile(const char *file) {

	int fd;
	char *blk = NULL;
	size_t blksz = 0;

	errno = 0;

	if (verbose)
		printf("%s %lld bytes\n", file, (unsigned long long)size);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, MODE);
	if (fd < 0) {
		error("Could not open %s: %s\n", file, strerror(errno));
		return -1;
	}

	if (!noalloc) {
		off_t written = 0;
		struct stat st;

		if (fstat(fd, &st) < 0) {
			error("Could not stat %s: %s\n", file, strerror(errno));
			goto exit;
		}
		if (blksz != st.st_blksize) {
			blksz = st.st_blksize;
			blk = calloc(blksz, 1);
			if (!blk) {
				error("Could not allocate buffer "
					"(%u bytes): %s\n", (unsigned) blksz,
					strerror(errno));
				goto exit;
			}
		}
		while(written < size) {
			ssize_t rc;
			size_t bytes = MIN(blksz, size - written);
			rc = write(fd, blk, bytes);
			if (rc < 0)
				rc = 0;
			written += rc;
			if (rc != bytes) {
				error("%s: written %lu of %lu bytes: %s\n",
					file, (unsigned long)written,
					(unsigned long)size, strerror(errno));
				goto exit;
			}
		}
	}

exit:
	if (blk)
		free(blk);
	if (close(fd) < 0) {
		error("Error encountered when closing %s: %s\n",
			file, strerror(errno));
	}
	return errno != 0;
}

int main(int argc, char *argv[]) {

	int errors = 0;

	if (argc < 2)
		usage();

	while (argv[1] && argv[1][0] == '-') {
		char *opt = &argv[1][0];
		while (*(++opt)) {
			if (*opt == 'v')
				verbose = 1;
			else if (*opt == 'n')
				noalloc = 1;
			else
				usage();
		}
		argc--;
		argv++;
	}

	if (argc >= 2) {
		size = parse_size(argv[1]);
		argc--;
		argv++;
	} else {
		usage();
	}

	while(argc > 1) {
		errors += mkfile(argv[1]);
		argc--;
		argv++;
	}
	return errors;
}