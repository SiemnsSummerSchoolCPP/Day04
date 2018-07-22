#include <istream>
#include "Utils.h"

int MinstTools::checkFirst2Bytes(std::istream& stream)
{
	u_char charBuf[2];
	stream.read((char*)charBuf, sizeof(charBuf));
	if (charBuf[0] != 0 || charBuf[1] != 0)
	{
		return -1;
	}

	return 0;
}
