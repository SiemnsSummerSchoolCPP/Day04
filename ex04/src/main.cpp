#include <fstream>
#include <iostream>

int printContents(std::ostream& o, const char* filePath)
{
	auto fileStream = std::fstream(filePath);
	if (!fileStream.is_open())
	{
		std::cerr << filePath << ": No such file!" << std::endl;
		return EXIT_FAILURE;
	}

	std::string buf;
	while (std::getline(fileStream, buf))
	{
		o << buf << "\n";
	}
	fileStream.close();
	return EXIT_SUCCESS;
}

std::string readTargetFile()
{
	std::string result;

	std::cout << "Input the file name." << std::endl;
	std::getline(std::cin, result);
	return result;
}

int main(int argc, const char** argv)
{
	if (argc == 1)
	{
		printContents(std::cout, readTargetFile().c_str());
	}
	else for (int i = 1; i < argc; i++)
	{
		printContents(std::cout, argv[i]);
	}
	return EXIT_SUCCESS;
}