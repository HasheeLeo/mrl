#include "AST.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include "ParserException.hpp"

#include <vector>

Parser::Parser(const std::vector<const Token*>& _tokens)
	: tokens(_tokens), syntaxTree()
{
}

const AST& Parser::Parse()
{
	const unsigned int maxTokens = tokens.size();
	unsigned int cur = 0;
	for (cur; cur < maxTokens; ++cur) {
		const TokenWord* tokenWord = dynamic_cast<const TokenWord*>(tokens[cur]);
		if (tokenWord) {
			
			// Check if there is an assignment token.
			const TokenAssignment* tokenAssign = dynamic_cast<const TokenAssignment*>(tokens[cur + 1]);
			if (!tokenAssign) {
				
				// "parent" variable must have an
				// r-value.
				if (tokenWord->GetValue() == "parent") {
					throw ParserException::MissingAssignment();
				}
			}
			else {

				// Get the r-value.
				cur += 2;

				const TokenInteger* tokenInt = dynamic_cast<const TokenInteger*>(tokens[cur]);
				if (tokenInt) {
				}

				const TokenPath* tokenPath = dynamic_cast<const TokenPath*>(tokens[cur]);
				if (tokenPath) {
				}

				const TokenString* tokenStr = dynamic_cast<const TokenString*>(tokens[cur]);
				if (tokenStr) {
				}

				else {
					throw ParserException::MissingRValue();
				}
			}
		}
	}
	return syntaxTree;
}
