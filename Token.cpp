#include "Token.hpp"

// Prototype
void assign_cstring(char* dest, const char* src);

// Token class
Token::Token(unsigned int _line)
	: line(_line)
{
}

Token::~Token()
{
}

unsigned int Token::GetLine() const
{
	return line;
}

// TokenAssignment class
TokenAssignment::TokenAssignment(unsigned int _line)
	: Token(_line)
{
}

const void* TokenAssignment::GetValue() const
{
	return nullptr;
}

// TokenBlockStart class
TokenBlockStart::TokenBlockStart(unsigned int _line)
	: Token(_line)
{
}

const void* TokenBlockStart::GetValue() const
{
	return nullptr;
}

// TokenBlockEnd class
TokenBlockEnd::TokenBlockEnd(unsigned int _line)
	: Token(_line)
{
}

const void* TokenBlockEnd::GetValue() const
{
	return nullptr;
}

// TokenComma class
TokenComma::TokenComma(unsigned int _line)
	: Token(_line)
{
}

const void* TokenComma::GetValue() const
{
	return nullptr;
}

// TokenInteger class
TokenInteger::TokenInteger(int _value, unsigned int _line)
	: Token(_line), value(_value)
{
}

const void* TokenInteger::GetValue() const
{
	return &value;
}

// TokenParenStart class
TokenParenStart::TokenParenStart(unsigned int _line)
	: Token(_line)
{
}

const void* TokenParenStart::GetValue() const
{
	return nullptr;
}

// TokenParenEnd class
TokenParenEnd::TokenParenEnd(unsigned int _line)
	: Token(_line)
{
}

const void* TokenParenEnd::GetValue() const
{
	return nullptr;
}

// TokenString class
TokenString::TokenString(const char* _value, unsigned int _line)
	: Token(_line), value(0)
{
	assign_cstring(value, _value);
}

TokenString::~TokenString()
{
	if (value) {
		delete[] value;
		value = 0;
	}
}

const void* TokenString::GetValue() const
{
	return value;
}

// TokenPath class
TokenPath::TokenPath(const char* _value, unsigned int _line)
	: TokenString(_value, _line)
{
}

// TokenWord class
TokenWord::TokenWord(const char* _value, unsigned int _line)
	: TokenString(_value, _line)
{
}
