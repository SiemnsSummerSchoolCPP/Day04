#include "SecretMsgGenerator.h"

static long long getRandBetween(const int min, const int max)
{
	return rand() % (max - min) + min;
}

/*
** Write count number of random bytes in the given stream.
*/

static inline void fillUpWithRandomChars(
	const size_t count,
	std::ofstream& stream)
{
	stream.seekp(0, std::ios::beg);
	for (size_t i = 0; i < count; i++)
	{
		u_char randomChar = rand() % std::numeric_limits<u_char>::max();
		stream.write((char*)&randomChar, sizeof(randomChar));
	}
	stream.seekp(0, std::ios::beg);
}

/*
** Seek every offset and write the corresponding secret character.
*/

static inline void printSecertMsg(
	size_t msgLen,
	const char* secretMsg,
	const std::unique_ptr<OffsetType[]>& offsets,
	std::ofstream& stream)
{
	for (size_t i = 0; i < msgLen; i++)
	{
		stream.seekp(offsets[i]);
		stream.write(&(secretMsg[i]), sizeof(char));
	}
}

static inline size_t getMinSize(const size_t msgLen)
{
	return sizeof(uint8_t) + (2 * msgLen * sizeof(OffsetType));
}

static inline uint8_t generateFirstByte(size_t minSize)
{
	return getRandBetween(minSize, std::numeric_limits<uint8_t>::max());
}

static inline OffsetType gerRandomOffset(size_t minSize, size_t maxSize)
{
	return getRandBetween(minSize, maxSize - sizeof(OffsetType));
}

void writeCodifiedText(SecretCodifierModel& model)
{
	size_t msgLen = strlen(model.secretMsg);
	size_t minSize = getMinSize(msgLen);
	uint8_t firstByte = generateFirstByte(minSize);
	size_t maxSize = firstByte * msgLen;

	fillUpWithRandomChars(maxSize, *model.outStream);
	model.outStream->write((char*)&firstByte, sizeof(firstByte));

	auto offsets = std::unique_ptr<OffsetType[]>(new OffsetType[msgLen]);
	for (size_t i = 0; i < msgLen; i++)
	{
		offsets[i] = gerRandomOffset(minSize, maxSize);
		model.outStream->write((char*)&(offsets[i]), sizeof(OffsetType));
	}

	printSecertMsg(msgLen, model.secretMsg, offsets, *model.outStream);
}