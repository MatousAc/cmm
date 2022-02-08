#pragma once
#include "../include.h"
#include "../scanner/Token.h"
#include "Expression.hpp"
using std::runtime_error;

// errors
struct ParseError : public runtime_error {
	//here we're using base = runtime_error;
	explicit ParseError(const string& message);
	explicit ParseError();
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
	Expression* ternary();
	Expression* comparison();
	Expression* term();
	Expression* factor();
	Expression* unary();
	Expression* primary();

	// helpers
	bool match(vector<TokenType> types);
	bool check(TokenType type);
	Token advance();
	bool isAtEnd();
	Token peek();
	Token previous();
	Token consume(TokenType type, string message);

	// errors
	ParseError error(Token token, string message);
	void synchronize();
};

