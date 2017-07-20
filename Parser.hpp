#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Token.hpp"

#include <vector>

class Parser
{
private:
	AST syntaxTree;
	const std::vector<const Token*>& tokens;

public:
	Parser(const std::vector<const Token*>& _tokens);

	const AST& Parse();
};

#endif // PARSER_HPP
