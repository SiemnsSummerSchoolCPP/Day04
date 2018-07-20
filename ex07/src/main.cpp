#include <fstream>
#include <iostream>

typedef struct PrefixedLinesPrinterModel
{
	std::ostream*	normalLinesStream = nullptr;
	std::ostream*	prefixedLinesStream = &std::cout;
	const char*		prefix;
} PrefixedLinesPrinterModel;

void printPrefixedLines(
	const PrefixedLinesPrinterModel& model,
	std::ifstream& fileStream)
{
	std::string buf;

	auto prefixLen = strlen(model.prefix);
	while (std::getline(fileStream, buf))
	{
		if (!buf.compare(0, prefixLen, model.prefix))
		{
			if (model.prefixedLinesStream != nullptr)
			{
				*model.prefixedLinesStream << buf << "\n";
			}
		}
		else
		{
			if (model.normalLinesStream != nullptr)
			{
				*model.normalLinesStream << buf << "\n";
			}
		}
	}
}

void printPrefixedLines(
	const PrefixedLinesPrinterModel& model,
	const char* filePath)
{
	std::ifstream fileStream;

	errno = 0;
	fileStream.open(filePath);
	if (!fileStream.is_open() || errno != 0)
	{
		std::cerr << filePath << ": " << strerror(errno);
		return;
	}

	printPrefixedLines(model, fileStream);
	fileStream.close();
}

int main(int argc, const char** argv)
{
	if (argc < 3)
	{
		std::cerr
			<< "Invalid arguments. Minimum 3 are required" << std::endl
			<< "The first argument must be the prefix" << std::endl;
	}

	auto model = PrefixedLinesPrinterModel();
	model.prefix = argv[1];
	model.prefixedLinesStream = &std::cout;
	model.normalLinesStream = nullptr;

	for (int i = 2; i < argc; i++)
	{
		printPrefixedLines(model, argv[i]);
	}
	return 0;
}