#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>

class Token
{
private:
	const unsigned int line;

public:
	Token(unsigned int _line);
	virtual ~Token();

	unsigned int GetLine() const;
	virtual const void* GetValue() const = 0;
};

class TokenAssignment : public Token
{
public:
	TokenAssignment(unsigned int _line);
	const void* GetValue() const;
};

class TokenBlockStart : public Token
{
public:
	TokenBlockStart(unsigned int _line);
	const void* GetValue() const;
};

class TokenBlockEnd : public Token
{
public:
	TokenBlockEnd(unsigned int _line);
	const void* GetValue() const;
};

class TokenComma : public Token
{
public:
	TokenComma(unsigned int _line);
	const void* GetValue() const;
};

class TokenInteger : public Token
{
private:
	const int value;

public:
	TokenInteger(int _value, unsigned int _line);

	const void* GetValue() const;
};

class TokenParenStart : public Token
{
public:
	TokenParenStart(unsigned int _line);
	const void* GetValue() const;
};

class TokenParenEnd : public Token
{
public:
	TokenParenEnd(unsigned int _line);
	const void* GetValue() const;
};

class TokenString : public Token
{
private:
	char* value;

public:
	TokenString(const char* _value, unsigned int _line);
	~TokenString();

	const void* GetValue() const;
};

class TokenPath : public TokenString
{
public:
	TokenPath(const char* _value, unsigned int _line);
};

class TokenWord : public TokenString
{
public:
	TokenWord(const char* _value, unsigned int _line);
};

#endif // TOKEN_HPP
