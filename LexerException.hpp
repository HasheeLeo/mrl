#ifndef LEXEREXCEPTION_HPP
#define LEXEREXCEPTION_HPP

namespace LexerException
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

class UntermStr : public Exception
{
public:
	UntermStr();
};

}

#endif // LEXEREXCEPTION_HPP
