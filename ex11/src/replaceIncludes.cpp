#include "replaceIncludes.h"
#include <regex>
#include <iostream>

static const bool kParsed = true;
static const std::regex kRegexInclude = 
	std::regex("^[ \t]*#[ \t]*include[ \t]*\"(.+)\"");
static const std::regex kRegexPragmaOnce =
	std::regex("^[ \t]*#[ \t]*pragma[ \t]+once.*");

static bool alreadyIncluded(
	const IncludeReplacerModel& model,
	const std::string& file)
{
	const auto& included = model.includedFiles;
	return std::find(included.begin(), included.end(), file) != included.end();
}

static bool parseInclude(
	IncludeReplacerModel& model,
	std::ostream& outStream,
	const std::string matchStr)
{
	auto file = model.rootDir + matchStr;
	if (alreadyIncluded(model, file))
	{
		return kParsed;
	}
	
	// If success.
	model.parseIterations++;
	if (replaceIncludes(model, outStream, file) == 0)
	{
		return kParsed;
	}

	return !kParsed;
}

void replaceIncludes(
	IncludeReplacerModel& model,
	const std::string currentFilePath,
	std::ostream& outStream,
	std::istream& inStream)
{
	std::string buf;
	std::string file;
	std::smatch match;

	if (model.parseIterations >= kMaxParsings)
		throw "Too many parsings.";
	
	while (std::getline(inStream, buf))
	{
		std::regex_search(buf, match, kRegexInclude);
		if (match.size() != 0)
		{
			if (parseInclude(model, outStream, match[1].str()) == kParsed)
				continue;
		}
		else if (std::regex_match(buf, kRegexPragmaOnce))
		{
			model.includedFiles.push_back(currentFilePath);
			continue;
		}

		outStream << buf << "\n";
	}
}
