#ifndef PARSEREXCEPTION_HPP
#define PARSEREXCEPTION_HPP

namespace ParserException
{

class Exception
{
private:
	char* error;

public:
	Exception(const char* _error);
	~Exception();

	const char* GetError();
};

class MissingAssignment : public Exception
{
public:
	MissingAssignment();
};

class MissingRValue : public Exception
{
public:
	MissingRValue();
};

}

#endif // PARSEREXCEPTION_HPP
