#include "replaceIncludes.h"
#include <fstream>
#include <iostream>

int replaceIncludes(
	IncludeReplacerModel& model,
	std::ostream& outStream,
	const std::string filePath)
{
	errno = 0;
	auto fileStream = std::ifstream(filePath);
	if (!fileStream.is_open() || errno != 0)
	{
		if (model.printInvalidFileWarning)
		{
			std::cerr << filePath << ": " << strerror(errno) << std::endl;
		}
		return -1;
	}

	model.printInvalidFileWarning = false;
	replaceIncludes(model, filePath, outStream, fileStream);
	fileStream.close();
	
	return 0;
}
