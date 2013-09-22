
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "readln.h"

void printbuf(char *buf, ssize_t len) {

	write(STDOUT_FILENO, "[", 1);
	write(STDOUT_FILENO, buf, len);
	write(STDOUT_FILENO, "]\n", 2);
}

int main(int argc, char **argv) {

	int fd, rc;
	char buf[32];

	if (argc < 2) {
		return 1;
	}

	fd = open(argv[1], O_RDONLY);

	if (fd < 0) {
		perror("open");
		return 1;
	}

	for(;;) {
		rc = readln(fd, buf, sizeof(buf));
		if (rc == 0)
			break; 
		if (rc < 0) {
			perror("readln");
			return 1;
		}
		printbuf(buf, rc);
	}

	return 0;
}
