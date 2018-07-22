#pragma once

#include <exception>

namespace MinstTools::Exceptions
{
	struct MinstToolsExecption : public std::exception {};

	struct FailedToOpenException : public MinstToolsExecption
	{
		const char* error;

		FailedToOpenException(const char* errorMsg) : error(errorMsg) {}
		const char* what() const throw() { return error; }
	};

	struct InvalidFormatException : public MinstToolsExecption
	{
		const char* what() const throw() { return "Invalid format"; }
	};
};
