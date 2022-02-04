#pragma once
#include "../include.h"
#include "Literal.h"

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
	string display();
	string toString();
};

// maps token types to their lexeme
//vector<string> tokenVec{
//	// Single-character tokens.
//	"(", ")", "{", "}",
//	",", ".", "-", "+", ";", "/", "*",
//
//	// One or two character tokens.
//	"!", "!=",
//	"=", "==",
//	">", ">=",
//	"<", "<=",
//
//	// Literals.
//	"IDENTIFIER", "STRING", "NUMBER",
//
//	// Keywords.
//	"and", "class", "else", "false", "fun", "for", "if", "nil", "or",
//	"print", "return", "super", "this", "true", "var", "while",
//
//	"EoF"
//};
