#include "LexerException.hpp"

// Prototype
void assign_cstring(char* dest, const char* src);

namespace LexerException
{

// Exception class
Exception::Exception(const char* _error)
	: error(0)
{
	assign_cstring(error, _error);
}

Exception::~Exception()
{
	if (error) {
		delete[] error;
		error = 0;
	}
}

const char* Exception::GetError()
{
	return error;
}

// UntermStr class
UntermStr::UntermStr()
	:Exception("unterminated string")
{
}

}