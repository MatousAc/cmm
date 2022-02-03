#pragma once
#include "../include.h"
#include "../cmm.h"
#include "../scanner/Token.h"
#include "../tools/LoxError.h"
#include "Expression.hpp"
using std::runtime_error;

// errors
struct ParseError : runtime_error {
	ParseError();
};

class Parser {
	vector<Token> tokens;
	int current;

public: // constructor
	Parser(vector<Token> tokens) : tokens{ tokens }, current{ 0 } {};
	Expression* parse();
private:
	Expression* expression();
	Expression* equality();
	Expression* comparison();
	Expression* term();
	Expression* factor();
	Expression* unary();
	Expression* primary();

	// helpers
	bool match(vector<tokenType> types);
	bool check(tokenType type);
	Token advance();
	bool isAtEnd();
	Token peek();
	Token previous();
	Token consume(tokenType type, string message);

	// errors
	//class ParseError std::runtime_error {
	//public:
	   // ParseError();
	//};
	ParseError error(Token token, string message);
	void synchronize();
};

