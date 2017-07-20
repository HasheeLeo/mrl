#include "Lexer.hpp"
#include "LexerException.hpp"
#include "Token.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

inline bool is_integer_value(char x)
{
	return (x >= 48 && x <= 57);
}

inline bool is_word_value(char x)
{
	return ((x >= 65 && x <= 90) || (x >= 97 && x <= 122) || x == 95);
}

inline bool is_path_value(char x)
{
	return (is_word_value(x) || x == 47);
}

Lexer::Lexer(const char* filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw LexerException::Exception("Failed to open the file.");
	}

	// Convert char* to std::string.
	std::stringstream ss;
	ss << file.rdbuf();
	source = ss.str();

	file.close();
}

Lexer::~Lexer()
{
	for (const Token* token : tokens) {
		if (token) {
			delete token;
			token = 0;
		}
	}
}

const std::string Lexer::ReadToken(unsigned int& cur, TokenType type)
{
	unsigned int tokenLength = 0;

	switch (type) {
		case INTEGER:
			while (is_integer_value(source[cur])) {
				++tokenLength;
				++cur;
			}
		break;

		case PATH:
			while (is_path_value(source[cur])) {
				++tokenLength;
				++cur;
			}
		break;
		
		case WORD:
			while (is_word_value(source[cur])) {
				++tokenLength;
				++cur;
			}
		break;
	}
	
	return source.substr(cur - tokenLength, tokenLength);
}

const TokenString* Lexer::String2Token(unsigned int& cur, unsigned int& curLine)
{
	std::string str;
	while (source[cur] != '\"') {

		// Found an escape sequence.
		if (source[cur] == '\\') {

			// Determine what is being escaped and
			// add the corresponding control
			// character.
			++cur;
			switch (source[cur]) {
				case '\"':
					str += '\"';
					++cur;
				break;

				case 'n':
					str += '\n';
					++cur;
				break;

				case 't':
					str += '\t';
					++cur;
				break;

				// Possible continuation character.
				case ' ':
				case '\n':
					while (source[cur] != '\n') {
						++cur;
					}

					++curLine;
					++cur;

					// Trim all whitespace after
					// the continuation character.
					while (source[cur] == ' ') {
						++cur;
					}
				break;

				// Possible DM-specfic control
				// character.
				default:
					str += "\\" + source[cur];
					++cur;
			}
		}

		// Reached the end of line without
		// encountering the end of string or
		// a continuation character.
		else if (source[cur] == '\n') {
			throw LexerException::UntermStr();
		}

		else {
			str += source[cur];
			++cur;
		}
	}
	
	// Skip past the ending quotation mark.
	++cur;

	return new TokenString(str.c_str(), curLine);
}

const std::vector<const Token*>& Lexer::Scan()
{
	const unsigned int sourceSize = source.size();

	unsigned int cur = 0;
	unsigned int curLine = 1;

	while (cur < sourceSize) {
		switch (source[cur]) {

			// Ignore whitespace and tabs.
			case ' ':
			case '\t':
				++cur;
			break;

			case '\n':
				++cur;
				++curLine;
			break;

			case '/':

				// Check if it is a comment.
				if (source[cur + 1] == '/') {

					// Skip to the end of the line.
					while (source[cur] != '\n') {
						++cur;
					}
				}

				// Probably a path value then.
				else {
					tokens.push_back(new TokenPath(ReadToken(cur, PATH).c_str(), curLine));
				}
			break;

			case '=':
				tokens.push_back(new TokenAssignment(curLine));
				++cur;
			break;

			case '{':
				tokens.push_back(new TokenBlockStart(curLine));
				++cur;
			break;

			case '}':
				tokens.push_back(new TokenBlockEnd(curLine));
				++cur;
			break;

			case '(':
				tokens.push_back(new TokenParenStart(curLine));
				++cur;
			break;

			case ')':
				tokens.push_back(new TokenParenEnd(curLine));
				++cur;
			break;

			case '\"':
			{
				// Skip past the quotation mark to
				// inside the string.
				++cur;

				tokens.push_back(String2Token(cur, curLine));
			}
			break;

			case ',':
				tokens.push_back(new TokenComma(curLine));
				++cur;
			break;

			case '-':
			case '+':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				tokens.push_back(new TokenInteger(std::stoi(ReadToken(cur, INTEGER)), curLine));
			break;

			// It is an identifier -- a word
			default:
				tokens.push_back(new TokenWord(ReadToken(cur, WORD).c_str(), curLine));
		}
	}
	return tokens;
}
