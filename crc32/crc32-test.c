
#include <stdio.h>
#include "crc32.h"

char block[128];

int main() {

	int i;
	struct crc32 c;
	
	for(i=0; i < sizeof(block); i++) {
		block[i] = i;
	}
	
	crc32_init(&c);
	
	for(i=0; i < 32; i++)
		crc32_block(block + (i * (sizeof(block) / 32)), 
			sizeof(block) / 32, &c);
	
	printf("block: %u\n", crc32_final(&c));
	
	printf("quick: %u\n", crc32(block, sizeof(block)));
	
	return 0;
}
