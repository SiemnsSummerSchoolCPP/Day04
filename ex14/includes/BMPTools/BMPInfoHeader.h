#pragma once

#include <inttypes.h>

typedef struct
{
	uint32_t infoHeaderSize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitsPerPixel;
	uint32_t compression = 0;
	uint32_t imgSize;
	uint32_t horizontalResolution = 0;
	uint32_t verticalResolution = 0;
	uint32_t colorsUsed;
	uint32_t importantColors;
} __attribute__((packed)) BMPInfoHeader;
