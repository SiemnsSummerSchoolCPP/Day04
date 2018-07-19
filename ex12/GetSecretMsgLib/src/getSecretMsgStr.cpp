#include "getSecretMsgStr.h"

std::string getSecretMsgStr(
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