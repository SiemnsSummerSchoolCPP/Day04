#include "getSecretMsgStr.h"

size_t getMessageLength(std::fstream& inputFile)
{
    auto fileSize = getFileSize(inputFile);
    auto firstByte = getFirstByte(inputFile);
	return fileSize / firstByte;
}