#include "BMPGrayscaleImg.hpp"
#include <fstream>
#include <iostream>

using namespace BMPTools;

static uint computePadding(uint width)
{
	if (width % 4 == 0)
	{
		return 0;
	}
	else
	{
		return (((width / 4) + 1) * 4) - width;
	}
}

BMPGrayscaleImg::BMPGrayscaleImg(
	const size_t width,
	const size_t height,
	const uint8_t* pixels)
{
	assignConstants();

	infoHeader.width = width;
	infoHeader.height = width;
	this->pixels = pixels;

	header.dataOffset =
		sizeof(BMPHeader) +
		sizeof(BMPInfoHeader) +
		paletteSize();

	infoHeader.imgSize = infoHeader.width * infoHeader.height;
	header.fileSize = header.dataOffset + infoHeader.width * infoHeader.height;
	
	padding = computePadding(infoHeader.width);
}

/*
** Public members.
*/

void BMPGrayscaleImg::print(const char* filePath) const
{
	auto outFile = std::ofstream(filePath, std::ios::binary);
	if (!outFile.is_open())
	{
		throw BMPGrayscaleImgExceptions::FailedToOpenException(
			(std::string(filePath) + ": " + strerror(errno)).c_str());
	}
	
	print(outFile);
	outFile.close();
}

void BMPGrayscaleImg::print(std::ostream& o) const
{
	printHeaders(o);
	printPixels(o);
}

/*
** Private members.
*/

uint BMPGrayscaleImg::paletteSize() const
{
	return infoHeader.colorsUsed * 4;
}

inline void BMPGrayscaleImg::assignConstants()
{
	infoHeader.infoHeaderSize = 40;
	infoHeader.planes = 1;
	infoHeader.bitsPerPixel = 8;
	infoHeader.compression = 0;
	infoHeader.horizontalResolution = 0;
	infoHeader.verticalResolution = 0;
	infoHeader.colorsUsed = 256;
	infoHeader.importantColors = 0;
}

inline void BMPGrayscaleImg::printPalette(std::ostream& o) const
{
	uint8_t rgbBytes[4];
	
	// Reserved byte.
	rgbBytes[3] = 0;
	
	for (int i = 0; i < 256; i++)
	{
		rgbBytes[0] = i;
		rgbBytes[1] = i;
		rgbBytes[2] = i;
		o.write((char*)rgbBytes, sizeof(rgbBytes));
	}
}

static inline void addPadding(std::ostream& o, uint padding)
{
	if (padding == 0)
		return;

	uint8_t buf = 0;
	for (int i = 0; i < padding; i++)
	{
		o.write((char*)&buf, sizeof(buf));
	}
}

template <typename T>
static inline void writeToStream(std::ostream& o, T data)
{
	o.write((char*)&data, sizeof(data));
}

inline void BMPGrayscaleImg::printHeaders(std::ostream& o) const
{
	assert(o.tellp() == 0);

	writeToStream(o, header);
	assert(o.tellp() == sizeof(BMPHeader));

	writeToStream(o, infoHeader);
	assert(o.tellp() == sizeof(BMPHeader) + sizeof(BMPInfoHeader));

	printPalette(o);
	assert(o.tellp() == header.dataOffset);
}

inline void BMPGrayscaleImg::printPixels(std::ostream& o) const
{
	for (uint i = 0; i < infoHeader.height; i++)
	{
		for (uint j = 0; j < infoHeader.width; j++)
		{
			uint pixelIndex = i * infoHeader.width + j;
			o.write((char*)&pixels[pixelIndex], sizeof(pixels[pixelIndex]));
		}
		addPadding(o, padding);
	}

	assert((uint)o.tellp() == header.fileSize);
}
