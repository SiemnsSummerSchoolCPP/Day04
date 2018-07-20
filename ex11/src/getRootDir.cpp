#include "replaceIncludes.h"
#include <regex>

const char* getRootDir(int argc, const char** argv)
{
	static const auto defaultRootDir = "./";

	for (int i = 1; i < argc; i++)
	{
		if (std::regex_match(argv[i], std::regex("rootDir=.*")))
		{
			return argv[i] + strlen("rootDir=");
		}
	}

	return defaultRootDir;
}
