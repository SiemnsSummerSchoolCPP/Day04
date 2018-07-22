#include "getSecretMsgStr.h"

std::string getSecretMsg(const char* filePath)
{
	auto inputFile = std::ifstream(filePath, std::ios::binary);

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