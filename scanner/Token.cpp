#include "Token.h"
Token::Token(tokenType type, string lexeme, Literal lit, int line)
	: type{ type }, lexeme{ lexeme },
	lit{ lit }, line{ line } {}

string Token::display() {
	string literal = "";
	if ((type == STRING) || (type == NUMBER))
		literal = lit.toString();
	return std::to_string(line) + ": " + std::to_string((int)type)
		+ "\t| " + lexeme + " \t" + literal;
}

string Token::toString() {
	//string literal = "";
	//if ((type == STRING) || (type == NUMBER))
	//	literal = lit.toString();
	//return tokenVec[(int)type];
	return lexeme;
}

vector<string> tokenVec {
	// Single-character tokens.
	"(", ")", "{", "}",
	",", ".", "-", "+", ";", "/", "*",

	// One or two character tokens.
	"!", "!=",
	"=", "==",
	">", ">=",
	"<", "<=",

	// Literals.
	"IDENTIFIER", "STRING", "NUMBER",

	// Keywords.
	"and", "class", "else", "false", "fun", "for", "if", "nil", "or",
	"print", "return", "super", "this", "true", "var", "while",

	"EoF"
};
