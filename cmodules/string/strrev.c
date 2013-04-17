
#include "string.h"

char* strrev(char *str) {

	char *st = str, *end = str + strlen(str) - 1;

	while(st < end) {
		char tmp = *end;
		*end-- = *st;
		*st++ = tmp;
	}
	return str;
}
