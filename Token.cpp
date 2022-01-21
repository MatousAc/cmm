#include "Token.h"
Token::Token(tokenType type, string lexeme, Literal lit, int line)
	: type{ type }, lexeme{ lexeme },
	lit{ lit }, line{ line } {}

string Token::toString() {
	string literal = "";
	if ((type == STRING) || (type == NUMBER))
		literal = lit.toString();
	return std::to_string(line) + ": " + std::to_string((int)type)
		+ "\t| " + lexeme + " \t" + literal;
}
