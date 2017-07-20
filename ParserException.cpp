#include "ParserException.hpp"

// Prototype
void assign_cstring(char* dest, const char* src);

namespace ParserException
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

// MissingAssignment class
MissingAssignment::MissingAssignment()
	: Exception("missing \'=\' after l-value")
{
}

// MissingRValue class
MissingRValue::MissingRValue()
	: Exception("missing r-value after \'=\'")
{
}

}
