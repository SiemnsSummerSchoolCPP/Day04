#include "MinstLabelDataSet.hpp"
#include "MinstToolsExceptions.h"
#include "Utils.h"
#include <fstream>

using namespace MinstTools;

MinstLabelDataSet::MinstLabelDataSet(const char* filePath)
{
	auto inStream = std::ifstream(filePath, std::ios::binary);
	if (!inStream.is_open())
		throw MinstTools::Exceptions::FailedToOpenException(strerror(errno));

	if (checkFirst2Bytes(inStream) != 0)
	{
		inStream.close();
		throw MinstTools::Exceptions::InvalidFormatException();
	}

	readFromStream(inStream, typeOfData);
	readFromStream(inStream, nbOfDimensions);
	readFromStream(inStream, nbOfItems);
	nbOfItems = swapEndian(nbOfItems);
	
	labels = new uint8_t[nbOfItems];
	inStream.read((char*)labels, sizeof(*labels) * nbOfItems);
	
	inStream.close();
}

MinstLabelDataSet::~MinstLabelDataSet()
{
	if (labels != nullptr)
		delete[] labels;
}
