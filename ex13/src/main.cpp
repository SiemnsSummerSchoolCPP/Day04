#include "SecretMsgGenerator.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <random>

static inline void printHelp()
{
	std::cout
		<< "First argument is a secret message, "
		<< "the second is the output file path." << std::endl;
}

static inline std::ofstream* getOutStream(const char* filePath)
{
	auto outFile = new std::ofstream(filePath, std::ios::binary);
	if (!outFile->is_open())
	{
		std::cerr << filePath << ": " << strerror(errno);
		exit(EXIT_FAILURE);
	}

	return outFile;
}

static inline void validateArguments(const int argc, const char** argv)
{
	if (argc == 1)
	{
		std::cerr << "Not enough arguments provided." << std::endl;
		printHelp();
		exit(EXIT_FAILURE);
	}
}

int main(const int argc, const char** argv)
{
	validateArguments(argc, argv);

	SecretCodifierModel model;
	model.secretMsg = argv[1];
	model.outStream = getOutStream(argv[2]);
	writeCodifiedText(model);
	return 0;
}