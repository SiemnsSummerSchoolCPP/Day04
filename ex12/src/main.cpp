#include <fstream>
#include <iostream>
#include <string.h>
#include "getSecretMsg.h"

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
			std::cout << getSecretMsg(argv[i]) << std::endl;
		}
		catch (int e) {}
	}
	return 0;
}
