#include "getSecretMsgStr.h"

std::string getSecretMsg(const char* filePath)
{
	auto inputFile = std::fstream(
		filePath,
		std::ios::in | std::ios::binary | std::ios::ate);

    if (!inputFile.is_open())
    {
        std::cerr << filePath << ": File not found" << std::endl;
        throw EXIT_FAILURE;
    }
 
 	auto msgLen = getMessageLength(inputFile);
 	auto offsets = getOffsets(msgLen, inputFile);
	auto result = getSecretMsgStr(msgLen, offsets, inputFile);
	inputFile.close();
	delete[] offsets;

	return result;
}