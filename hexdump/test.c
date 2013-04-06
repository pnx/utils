
#include "hexdump.h"

int main() {

	int i;
	char buf[130];

	for(i=0; i < sizeof(buf); i++)
		buf[i] = i;

	hexdump(buf, sizeof buf);

	return 0;
}
