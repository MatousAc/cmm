#include "Token.h"

Token::Token(tokenType type, string lexeme, string literal, int line)
	: type{ type }, lexeme{ lexeme },
	literal{ literal }, line{ line } {}

string Token::toString() {
	return lexeme + " " + literal;
}