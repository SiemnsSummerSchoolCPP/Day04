#include "MinstImgDataSet.hpp"
#include "MinstToolsExceptions.h"
#include "Utils.h"
#include <fstream>

using namespace MinstTools;

int MinstImgDataSet::totalNbOfPixels() const
{
	return nbOfRows * nbOfColumns;
}

/*
** Constructor.
*/

MinstImgDataSet::MinstImgDataSet(const char* filePath)
{
	auto inStream = std::ifstream(filePath, std::ios::binary);
	if (!inStream.is_open())
	{
		throw MinstTools::Exceptions::FailedToOpenException(
			(std::string(filePath) + ": " + strerror(errno)).c_str());
	}
	
	if (checkFirst2Bytes(inStream) != 0)
	{
		inStream.close();
		throw MinstTools::Exceptions::InvalidFormatException();
	}

	readFromStream(inStream, typeOfData);
	readFromStream(inStream, nbOfDimensions);
	readFromStream(inStream, nbOfImages);
	readFromStream(inStream, nbOfRows);
	readFromStream(inStream, nbOfColumns);

	nbOfImages = swapEndian(nbOfImages);
	nbOfRows = swapEndian(nbOfRows);
	nbOfColumns = swapEndian(nbOfColumns);

	loadImages(inStream);
	inStream.close();
}

MinstImgDataSet::~MinstImgDataSet()
{
	if (images != nullptr)
	{
		for (int i = 0; i < nbOfImages; i++)
			delete[] images[i];
			
		delete[] images;
	}
}

/*
** Private members.
*/

void MinstImgDataSet::loadImages(std::istream& inStream)
{
	images = new uint8_t*[nbOfImages];
	for (int i = 0; i < nbOfImages; i++)
	{
		images[i] = new uint8_t[totalNbOfPixels()];
		for (int j = 0; j < totalNbOfPixels(); j++)
		{
			inStream.read((char*)&(images[i][j]), sizeof(images[i][j]));
		}
	}
}
