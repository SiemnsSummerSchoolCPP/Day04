#pragma once

#include <inttypes.h>
#include <ostream>
#include "BMPHeader.h"
#include "BMPInfoHeader.h"

static_assert(sizeof(BMPHeader) == 14);
static_assert(sizeof(BMPInfoHeader) == 40);

namespace BMPTools
{
	class BMPGrayscaleImg
	{
	public:
		BMPGrayscaleImg(size_t width, size_t height, const uint8_t* pixels);

		void print(const char* filePath) const;
		void print(std::ostream& o) const;
		
	private:
		BMPHeader header;
		BMPInfoHeader infoHeader;
		const uint8_t* pixels;
		uint padding;
		
		inline uint paletteSize() const;
		
		inline void assignConstants();
		inline void printPalette(std::ostream& o) const;
		inline void printHeaders(std::ostream& o) const;
		inline void printPixels(std::ostream& o) const;
	};
};

namespace BMPTools::BMPGrayscaleImgExceptions
{
	struct BMPToolsExecption : public std::exception {};

	struct FailedToOpenException : public BMPToolsExecption
	{
		const char* error;

		FailedToOpenException(const char* errorMsg) : error(errorMsg) {}
		const char* what() const throw() { return error; }
	};
};
