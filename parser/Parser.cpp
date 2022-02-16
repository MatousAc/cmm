#include "Parser.h"
#include "../tools/LoxError.h"
#include "../tools/AstPrinter.h"
#include <typeinfo>

vector<Stmt*> Parser::parse() {
	vector<Stmt*> statements{};
	while (!isAtEnd()) {
		statements.push_back(declaration());
	}
	return statements;
}

Stmt* Parser::declaration() {
	try {
		if (match({ VAR })) return varDeclaration();
		return statement();
	}
	catch (ParseError error) {
		// keep parsing if possible
		synchronize();
		return NULL;
	}
}

Stmt* Parser::varDeclaration() {
	Token name = consume(IDENTIFIER, "Expect variable name.");

	Expr* initilizer = NULL;
	if (match({ EQUAL })) initilizer = expression();

	consume(SEMICOLON, "Expect ';' after variable declaration.");
	return new Var(name, initilizer);
}

Stmt* Parser::statement() {
	if (match(vector{ PRINT })) return printStatement();
	return expressionStatement();
}

Stmt* Parser::printStatement() {
	Expr* value = expression();
	consume(SEMICOLON, "Expect ';' after value.");
	return new Print(value);
}

Stmt* Parser::expressionStatement() {
	Expr* expr = expression();
	consume(SEMICOLON, "Expect ';' after expression.");
	return new Expression(expr);
}

Expr* Parser::expression() { return assignment(); }

Expr* Parser::assignment() {
	Expr* expression = ternary();

	if (match({ EQUAL })) {
		Token equals = previous();
		Expr* value = assignment();

		if (typeid(expression) == typeid(Variable)) {
			Token name = ((Variable*) expression)->name;
			return new Assign(name, value);
		}

		perr(equals, "Invalid assignment target.");
	}
	return expression;
}

Expr* Parser::ternary() {
	Expr* condition = equality();
	while (match(vector<TokenType>{ QUEST })) {
		Expr* ifTrue;
		Expr* ifFalse;
		ifTrue = expression();
		if (!match(vector{ COLON })) {
			advance(); // get to the EoF
			throw perr(previous(), "Expect '?' to have matching ':'.");
		}
		ifFalse = expression();
		return new Ternary(condition, ifTrue, ifFalse);
	}
	return condition;
}

Expr* Parser::equality() {
	Expr* expression = comparison();

	while (match(vector<TokenType>{ BANG_EQUAL, EQUAL_EQUAL })) {
		Token op = previous();
		Expr* right = comparison();
		expression = new Binary(expression, op, right);
	}
	return expression;
}

Expr* Parser::comparison() {
	Expr* expr = term();

	while (match(vector<TokenType>{ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
		Token op = previous();
		Expr* right = term();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::term() {
	Expr* expression = factor();

	while (match(vector<TokenType>{ MINUS, PLUS })) {
		Token op = previous();
		Expr* right = factor();
		expression = new Binary(expression, op, right);
	}
	return expression;
}

Expr* Parser::factor() {
	Expr* expression = unary();

	while (match(vector<TokenType>{ SLASH, STAR })) {
		Token op = previous();
		Expr* right = unary();
		expression = new Binary(expression, op, right);
	}
	return expression;
}

Expr* Parser::unary() {
	if (match(vector<TokenType>{BANG, MINUS})) {
		Token op = previous();
		Expr* right = unary();
		return new Unary(op, right);
	}
	return primary();
}

Expr* Parser::primary() {
	// we take false, true, or nil and create a Literal that holds a LoxType
	if (match(vector<TokenType>{FALSE})) return new Literal(LoxType{ false });
	if (match(vector<TokenType>{TRUE})) return new Literal(LoxType{ true });
	if (match(vector<TokenType>{NIL})) return new Literal(LoxType{});

	// package a LitVal as a LoxType and store it in Literal
	if (match(vector<TokenType>{NUMBER, STRING})) {
		return new Literal(LoxType{ previous().lit.retrieve() });
	}

	if (match({ IDENTIFIER })) {
		return new Variable{ previous() };
	}

	if (match(vector<TokenType>{LEFT_PAREN})) {
		Expr* expressionVar = expression();
		consume(RIGHT_PAREN, "Expect ')' after expression.");
		return new Grouping(expressionVar);
	}
	throw perr(peek(), "Expected expression match ");
}

// helpers
bool Parser::match(vector<TokenType> types) {
	auto type = types.begin();
	auto end = types.end();
	while (type != end) {
		if (check(*type)) {
			advance();
			return true;
		}
		type++;
	}
	return false;
}

bool Parser::check(TokenType type) {
	if (isAtEnd())
		return false;
	return peek().type == type;
}

Token Parser::consume(TokenType type, string message) {
	if (check(type)) return advance();
	throw perr(peek(), message);
}

Token Parser::advance() {
	if (!isAtEnd())
		current++;
	return previous();
}

bool Parser::isAtEnd() { return peek().type == EoF; }

Token Parser::peek() { return tokens[current]; }

Token Parser::previous() { return tokens[current - 1]; }

// errors
ParseError Parser::perr(Token token, string message) {
	err->error(token, message);
	return ParseError();
}

void Parser::synchronize() {
	advance();

	while (!isAtEnd()) {
		if (previous().type == SEMICOLON) return;

		switch (peek().type) {
		case CLASS:
		case FUN:
		case VAR:
		case FOR:
		case IF:
		case WHILE:
		case PRINT:
		case RETURN:
			return;
		}

		advance();
	}
}

ParseError::ParseError() : runtime_error{ "" } {}
ParseError::ParseError(const string& message) : runtime_error{ message.c_str() } {}