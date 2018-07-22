#include <fstream>
#include <iostream>
#include <climits>
#include <utility>

typedef struct
{
	const uint8_t signature[2] = { 'B', 'M' };
	uint32_t fileSize;
	const uint32_t reserved = 0;
	uint32_t dataOffset;

	void print(std::ostream& o) const;
} __attribute__((packed)) BMPHeader;

typedef struct
{
	const uint32_t infoHeaderSize = 40;
	uint32_t width;
	uint32_t height;
	const uint16_t planes = 1;
	const uint16_t bitsPerPixel = 8;
	const uint32_t compression = 0;
	uint32_t imgSize = 0;
	uint32_t horizontalResolution = 0;
	uint32_t verticalResolution = 0;
	const uint32_t colorsUsed = 256;
	const uint32_t importantColors = 0;

	void print(std::ostream& o) const;
} __attribute__((packed)) BMPInfoHeader;

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	const uint8_t reserved = 0;
} RGBPaletteEntry;	


class BMPImgData
{
public:
	BMPHeader header;
	BMPInfoHeader infoHeader;
	uint8_t* pixels;

	void print(std::ostream& o) const;
};

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

const uint palleteSize = 256 * 4;
static void printGrayscalePallete(std::ostream& o)
{
	auto RGBEntry = RGBPaletteEntry();

	for (int i = 0; i < 256; i++)
	{
		RGBEntry.r = i;
		RGBEntry.g = i;
		RGBEntry.b = i;
		o.write((char*)&RGBEntry, sizeof(RGBEntry));
	}
}

template <typename T>
void writeToStream(std::ostream& o, T data)
{
	o.write((char*)&data, sizeof(data));
}

void BMPHeader::print(std::ostream& o) const
{
	o.write((char*)signature, sizeof(signature));
	writeToStream(o, fileSize);
	writeToStream(o, reserved);
	writeToStream(o, dataOffset);
}

void BMPInfoHeader::print(std::ostream& o) const
{
	writeToStream(o, infoHeaderSize);
	writeToStream(o, width);
	writeToStream(o, height);
	writeToStream(o, planes);
	writeToStream(o, bitsPerPixel);
	writeToStream(o, compression);
	writeToStream(o, imgSize);
	writeToStream(o, horizontalResolution);
	writeToStream(o, verticalResolution);
	writeToStream(o, colorsUsed);
	writeToStream(o, importantColors);
}

void BMPImgData::print(std::ostream& o) const
{
	assert(o.tellp() == 0);

	o.write((char*)&header, sizeof(header));
	assert(o.tellp() == sizeof(BMPHeader));

	o.write((char*)&infoHeader, sizeof(infoHeader));
	assert(o.tellp() == sizeof(BMPHeader) + sizeof(BMPInfoHeader));

	printGrayscalePallete(o);
	assert(
		o.tellp() == sizeof(BMPHeader) + sizeof(BMPInfoHeader) + palleteSize);

	uint padding;
	if (infoHeader.width % 4 == 0)
	{
		padding = 0;
	}
	else
	{
		padding = (((infoHeader.width / 4) + 1) * 4) - infoHeader.width;
	}

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

static inline void printInvalidArgimentsMsg(std::ostream& o)
{
	o <<
		"Invalid arguments" << std::endl <<
		"The first argument must be a MINST image training set" << std::endl;
}

template <typename T>
T swapEndian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

void simple4x4BMPTest(const char* outFilePath)
{
	auto bmpImgData = BMPImgData();

	bmpImgData.header.dataOffset = 
		sizeof(BMPHeader) + sizeof(BMPInfoHeader) + palleteSize;

	bmpImgData.infoHeader.width = 4;
	bmpImgData.infoHeader.height = 4;

	auto pixels = new uint8_t[4 * 4];
	pixels[0] = 	200;
	pixels[1] = 	155;
	pixels[2] = 	255;
	pixels[3] = 	255;
	pixels[4] = 	255;
	pixels[5] = 	255;
	pixels[6] = 	255;
	pixels[7] = 	50;
	pixels[8] = 	255;
	pixels[9] = 	255;
	pixels[10] = 	255;
	pixels[11] = 	255;
	pixels[12] = 	255;
	pixels[13] = 	255;
	pixels[14] = 	255;
	pixels[15] = 	255;
	bmpImgData.pixels = pixels;

	bmpImgData.infoHeader.imgSize =
		bmpImgData.infoHeader.width * bmpImgData.infoHeader.height;

	bmpImgData.header.fileSize =
		sizeof(BMPHeader) + sizeof(BMPInfoHeader) + palleteSize + 
		bmpImgData.infoHeader.width * bmpImgData.infoHeader.height;

	auto outFile = std::ofstream(outFilePath, std::ios::binary);
	if (!outFile.is_open())
	{
		std::cerr << outFilePath << ": " << strerror(errno);
		exit(EXIT_FAILURE);
	}
	bmpImgData.print(outFile);
}

void flipBMPPixels(uint8_t* pixels, const uint widht, const uint height)
{
	for (uint i = 0; i < height / 2; i++)
	{
		for (uint j = 0; j < widht; j++)
		{
			const auto index1 = i * widht + j;
			const auto index2 = (height - i - 1) * widht + j;
			std::swap(pixels[index1], pixels[index2]);
		}
	}
}

int main(const int argc, const char** argv)
{
	if (argc < 3)
	{
		printInvalidArgimentsMsg(std::cerr);
		exit(EXIT_FAILURE);
	}

	auto inStream = std::ifstream(argv[1], std::ios::binary);
	if (!inStream.is_open())
	{
		std::cerr
			<< argv[1] << ": " << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}

	u_char charBuf[2];
	inStream.read((char*)charBuf, sizeof(charBuf));
	if (charBuf[0] != 0 || charBuf[1] != 0)
	{
		std::cerr <<
			"The first 2 bytes must be 0" << std::endl;
		exit(EXIT_FAILURE);
	}

	int8_t typeOfData;
	int8_t nbOfDimensions;

	inStream.read((char*)&typeOfData, sizeof(typeOfData));
	inStream.read((char*)&nbOfDimensions, sizeof(nbOfDimensions));

	int32_t nbOfImages;
	inStream.read((char*)&nbOfImages, sizeof(nbOfImages));
	nbOfImages = swapEndian(nbOfImages);

	int32_t nbOfRows;
	int32_t nbOfColumns;

	inStream.read((char*)&nbOfRows, sizeof(nbOfRows));
	inStream.read((char*)&nbOfColumns, sizeof(nbOfColumns));

	nbOfRows = swapEndian(nbOfRows);
	nbOfColumns = swapEndian(nbOfColumns);
	
	auto totalNbOfPixels = nbOfRows * nbOfColumns;

	auto images = new uint8_t*[nbOfImages];
	for (int i = 0; i < 100; i++)
	{
		images[i] = new uint8_t[totalNbOfPixels];
		for (int j = 0; j < totalNbOfPixels; j++)
		{
			inStream.read((char*)&(images[i][j]), sizeof(images[i][j]));
		}
	}

	assert(sizeof(BMPHeader) == 14);
	assert(sizeof(BMPInfoHeader) == 40);
	assert(sizeof(RGBPaletteEntry) == 4);
	
	auto outFilePath = argv[2];
	
	auto bmpImgData = BMPImgData();

	bmpImgData.header.dataOffset = 
		sizeof(BMPHeader) + sizeof(BMPInfoHeader) + palleteSize;

	bmpImgData.infoHeader.width = nbOfRows;
	bmpImgData.infoHeader.height = nbOfColumns;
	bmpImgData.pixels = images[4];
	flipBMPPixels(bmpImgData.pixels, bmpImgData.infoHeader.width, bmpImgData.infoHeader.height);

	bmpImgData.infoHeader.imgSize =
		bmpImgData.infoHeader.width * bmpImgData.infoHeader.height;

	bmpImgData.header.fileSize =
		sizeof(BMPHeader) + sizeof(BMPInfoHeader) + palleteSize + 
		bmpImgData.infoHeader.width * bmpImgData.infoHeader.height;

	auto outFile = std::ofstream(outFilePath, std::ios::binary);
	if (!outFile.is_open())
	{
		std::cerr << outFilePath << ": " << strerror(errno);
		exit(EXIT_FAILURE);
	}
	bmpImgData.print(outFile);
	return EXIT_SUCCESS;
}