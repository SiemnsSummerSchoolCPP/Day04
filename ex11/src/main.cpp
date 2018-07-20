#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include "replaceIncludes.h"

int main(int argc, const char** argv)
{
	if (argc == 1)
	{
		std::cerr << "No files provided" << std::endl;
		return EXIT_FAILURE;
	}

	auto rootDir = getRootDir(argc, argv);
	for (int i = 1; i < argc; i++)
	{
		auto model = IncludeReplacerModel();
		model.rootDir = rootDir;

		// Skip if it was a rootDir option.
		if (std::regex_match(argv[i], std::regex("rootDir=.*")))
			continue;

		try
		{
			replaceIncludes(model, std::cout, std::string(argv[i]));
		}
		catch (const char* e)
		{
			std::cerr << e << std::endl;
		}
		
	}
	return EXIT_SUCCESS;
}
