#include "Token.h"

Token::Token(tokenType type, string lexeme, Literal lit, int line)
	: type{ type }, lexeme{ lexeme },
	lit{ lit }, line{ line } {}

string Token::toString() {
	return lexeme + " " + lit.toString();
}