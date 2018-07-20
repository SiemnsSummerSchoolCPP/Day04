#ifndef _REPLACE_INCLUDES_H_
# define _REPLACE_INCLUDES_H_

#include <string>
#include <vector>

const int kMaxParsings = 20;

typedef struct IncludeReplacerModel
{
	bool							printInvalidFileWarning = true;
	int								parseIterations = 0;
	const char*						rootDir;
	std::vector<const std::string>	includedFiles;
} IncludeReplacerModel;

const char* getRootDir(int argc, const char** argv);

int replaceIncludes(
	IncludeReplacerModel& model,
	std::ostream& outStream,
	std::string filePath);

void replaceIncludes(
	IncludeReplacerModel& model,
	const std::string currentFilePath,
	std::ostream& outStream,
	std::istream& inStream);

#endif