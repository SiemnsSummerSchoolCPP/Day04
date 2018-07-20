#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

const int kDefaultNbOfLinesToPrint = 5;

int tailFile(int nbOfLines, std::ifstream& fileStream)
{
	int filePos;
	int nbOfLinesWritten;
	std::stringstream buf;

	nbOfLinesWritten = 0;
	fileStream.seekg(0, std::ios::end);
	filePos = fileStream.tellg();

	while (filePos != 0 && nbOfLinesWritten < nbOfLines)
	{
		char c;

		filePos--;
		if (filePos == 0)
			break;

		fileStream.seekg(filePos, std::ios::beg);
		c = fileStream.get();
		
		if (c == '\n')
			nbOfLinesWritten++;

		if (nbOfLinesWritten < nbOfLines)
			buf << c;
	}

	auto toPrint = buf.str();
	std::reverse(toPrint.begin(), toPrint.end());
	std::cout << toPrint;

	return nbOfLinesWritten;
}

int tailFile(int nbOfLines, const char* filePath)
{
	std::ifstream fileStream;

	fileStream.open(filePath, std::ios_base::binary);
	if (!fileStream.is_open())
	{
		std::cerr
			<< filePath
			<< ": Failed to open: "
			<< strerror(errno)
			<< std::endl;
		return -1;
	}

	tailFile(nbOfLines, fileStream);
	fileStream.close();
	return 0;
}

int main(int argc, const char** argv)
{
	if (argc == 1)
	{
		std::cerr << "No files provided" << std::endl;
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++)
	{
		tailFile(kDefaultNbOfLinesToPrint, argv[i]);
	}
	
	return EXIT_SUCCESS;
}