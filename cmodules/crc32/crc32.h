
#ifndef CRC32_H
#define CRC32_H

#include <stdint.h>

/* this struct is used for the block version,
   this is done so that the user will have a struct
   right up to the point where he wants to extract the final value. 
   So you can't modify the crc value by mistake. */
struct crc32 {
	uint32_t value;
};

void crc32_init(struct crc32 *crc);

void crc32_block(const void *data, unsigned size, struct crc32 *crc);

uint32_t crc32_final(struct crc32 *crc);

/* Single block version. */
uint32_t crc32(const void *data, unsigned size);

#endif /* CRC32_H */
