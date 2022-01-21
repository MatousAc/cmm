#pragma once
#include <string>
#include "Literal.h"
using std::string;

enum tokenType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	EoF
};

struct Token {
	tokenType type;
	string lexeme;
	Literal lit;
	int line;
	
	// constructors
	Token(tokenType type, string lexeme, Literal lit, int line);

	// methods
	string toString();
	// operator overloads
	//friend std::ostream& operator<<(std::ostream& os, const Token& tok);
};
