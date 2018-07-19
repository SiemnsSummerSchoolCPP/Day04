#include "getSecretMsgStr.h"

size_t getFileSize(std::fstream& inputFile)
{
	inputFile.seekg(0, std::ios::end);
	return inputFile.tellg();
}