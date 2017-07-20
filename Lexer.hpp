#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

#include "Token.hpp"

enum TokenType
{
	INTEGER,
	PATH,
	WORD
};

class Lexer
{
private:
	std::string source;
	std::vector<const Token*> tokens;

	const std::string ReadToken(unsigned int& cur, TokenType type);
	const TokenString* String2Token(unsigned int& cur, unsigned int& curLine);

public:
	Lexer(const char* filename);
	~Lexer();

	const std::vector<const Token*>& Scan();
};

#endif // LEXER_HPP
