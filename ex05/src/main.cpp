#include <iostream>
#include <fstream>

const char* kInputFilePath = "./aux/input.dat";
const char* kOutputFilePath = "./aux/output.dat";

void printFileOpenError(const char* filePath)
{
	std::cerr
		<< filePath
		<< ": Failed to open: "
		<< strerror(errno)
		<< std::endl;
}

static void openFile(
	const char* path,
	std::fstream& fileStream,
	const std::ios::openmode& mode)
{
	fileStream.open(path, mode);
	if (!fileStream.is_open())
		printFileOpenError(path);
}

static void openFiles(
	std::fstream& infile,
	std::fstream& outfile,
	int argc,
	const char** argv)
{
	const char* inFilePath;
	const char* outFilePath;

	if (argc == 3)
	{
		inFilePath = argv[1];
		inFilePath = argv[2];
	}
	else
	{
		inFilePath = kInputFilePath;
		outFilePath = kOutputFilePath;
	}

	openFile(inFilePath, infile, std::ios_base::in);
	openFile(outFilePath, outfile, std::ios_base::out);
}

int main(int argc, const char** argv)
{
	int				num1, num2;
	std::fstream	infile, outfile;

	openFiles(infile, outfile, argc, argv);
	if (errno == 0)
	{
		infile >> num1 >> num2;
		outfile << "Sum = " << (num1 + num2) << std::endl;
	}

	infile.close();
	outfile.close();
	return errno;
}