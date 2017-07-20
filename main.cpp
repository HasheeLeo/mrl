#include <iostream>

#include "Lexer.hpp"
#include "LexerException.hpp"

void assign_cstring(char* dest, const char* src)
{
	const size_t strLen = strlen(src);
	dest = new char[strLen + 1];
	strncpy(dest, src, strLen);
	dest[strLen] = '\0';
}

int main()
{
	try {
		Lexer lex("citizens.txt");
		lex.Scan();
	}
	catch (char* error) {
		std::cerr << error;
	}
	catch (LexerException::Exception& error) {
		std::cerr << error.GetError();
	}
	
	std::cin.get();
	return 0;
}
