
#include "string.h"
#include <stdio.h>

void test_strrev() {

	char k[] = "1aaaaaaaaaaa3aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2";

	printf("norm: %s\n", k);
	printf("rev: %s\n", strrev(k));
}

void test_memcpy_sb() {

	int i;
	char src[] = "123456789";
	char dest[4];

	memcpy_sb(dest, sizeof(dest), src, sizeof(src));

	for(i=0; i < sizeof(dest); i++)
		putc(dest[i], stdout);
}


int main() {

	test_strrev();
	test_memcpy_sb();
	
	return 0;
}
