#include "getSecretMsgStr.h"

OffsetType* getOffsets(const size_t msgLen, std::ifstream& inputFile)
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