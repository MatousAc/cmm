#pragma once
#include "../include.h"
#include "../scanner/Token.h"
#include "Expr.hpp"
#include "Stmt.hpp"
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
	vector<Stmt*> parse();
private:
	Stmt* statement();
	Stmt* printStatement();
	Stmt* expressionStatement();
	Expr* expression();
	Expr* equality();
	Expr* ternary();
	Expr* comparison();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();

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

