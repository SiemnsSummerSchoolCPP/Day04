#include "getSecretMsgStr.h"

uint8_t getFirstByte(std::ifstream& inputFile)
{
	uint8_t firstByte;

	inputFile.seekg(0, std::ios::beg);
	inputFile.read((char*)&firstByte, sizeof(firstByte));

	return firstByte;
}