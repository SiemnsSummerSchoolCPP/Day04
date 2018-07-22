#pragma once

#include <inttypes.h>

typedef struct
{
	uint8_t const signature[2] = { 'B', 'M' };
	uint32_t fileSize;
	uint32_t const reserved = 0;
	uint32_t dataOffset;
} __attribute__((packed)) BMPHeader;
