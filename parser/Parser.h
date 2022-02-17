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
	Stmt* declaration();
	Stmt* varDeclaration();
	Stmt* statement();
	Stmt* ifStatement();
	Stmt* printStatement();
	Stmt* expressionStatement();
	vector<Stmt*> block();

	Expr* expression();
	Expr* ternary();
	Expr* Or(); // or && and are reserved
	Expr* And();
	Expr* assignment();
	Expr* equality();
	Expr* comparison();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();

	// helpers
	bool match(vector<TokenType> types);
	Token consume(TokenType type, string message);
	bool check(TokenType type);
	Token advance();
	bool isAtEnd();
	Token peek();
	Token previous();

	// errors
	ParseError perr(Token token, string message);
	void synchronize();
};

