
#include "string.h"
#include <stdio.h>

void test_strrev() {

	char k[] = "1aaaaaaaaaaa3aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2";

	printf("norm: %s\n", k);
	printf("rev: %s\n", strrev(k));
}


int main() {

	test_strrev();
	
	return 0;
}
