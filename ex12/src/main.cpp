#include <fstream>
#include <iostream>
#include <string.h>

#define BINARY_FILE_FLAGS (std::ios::in | std::ios::binary | std::ios::ate)

const int noProvidedFilesException = 42;
const int fileNotFoundException = noProvidedFilesException + 1;

using OffsetType = int16_t;

size_t getFileSize(std::fstream& inputFile)
{
	inputFile.seekg(0, std::ios::end);
	return inputFile.tellg();
}

uint8_t getFirstByte(std::fstream& inputFile)
{
	uint8_t firstByte;

	inputFile.seekg(0, std::ios::beg);
	inputFile.read((char*)&firstByte, sizeof(firstByte));

	return firstByte;
}

size_t getMessageLength(std::fstream& inputFile)
{
    auto fileSize = getFileSize(inputFile);
    auto firstByte = getFirstByte(inputFile);
	return fileSize / firstByte;
}

OffsetType* getOffsets(const size_t msgLen, std::fstream& inputFile)
{
	OffsetType* result;

	result = new OffsetType[msgLen];
	inputFile.seekg(sizeof(uint8_t), std::ios::beg);
	for (int i = 0; i < msgLen; i++)
	{
		OffsetType offset;
		inputFile.read((char*)&offset, sizeof(offset));

		result[i] = offset;
	}
	return result;
}

std::string getSecretMsg(
	const size_t msgLen,
	const OffsetType* offsets,
	std::fstream& inputFile)
{
	char* charArray;

	charArray = new char[msgLen];
	for (int i = 0; i < msgLen; i++)
	{
		inputFile.seekg(offsets[i], std::ios::beg);
		inputFile.read((char*)&(charArray[i]), sizeof(*charArray));
	}

	auto result = std::string(charArray);
	delete[] charArray;
	return result;
}

std::string getSecretMsgFromFile(const char* filePath)
{
	auto inputFile = std::fstream(filePath, BINARY_FILE_FLAGS);

    if (!inputFile.is_open())
    {
        std::cerr << filePath << ": File not found" << std::endl;
        throw fileNotFoundException;
    }
 
 	auto msgLen = getMessageLength(inputFile);
 	auto offsets = getOffsets(msgLen, inputFile);
	auto result = getSecretMsg(msgLen, offsets, inputFile);
	inputFile.close();
	delete[] offsets;

	return result;
}

int main(int argc, const char** argv)
{
	if (argc == 1)
	{
		std::cerr << "No file provided" << std::endl;
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++)
	{
		try
		{
			std::cout << getSecretMsgFromFile(argv[i]) << std::endl;
		}
		catch (int e)
		{
		}
	}
	return 0;
}
