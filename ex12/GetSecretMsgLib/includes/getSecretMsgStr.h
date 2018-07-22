#ifndef _GET_SECRET_MSG_STR_H_
# define _GET_SECRET_MSG_STR_H_

# include <fstream>
# include <iostream>
# include <string.h>

using OffsetType = uint16_t;

size_t		getFileSize(std::ifstream& inputFile);
uint8_t		getFirstByte(std::ifstream& inputFile);
size_t		getMessageLength(std::ifstream& inputFile);
OffsetType*	getOffsets(const size_t msgLen, std::ifstream& inputFile);
std::string	getSecretMsgStr(
				size_t msgLen,
				const OffsetType* offsets,
				std::ifstream& inputFile);

#endif