#include "Parser.h"
#include "../tools/LoxError.h"

Expr* Parser::parse() {
	try { return expression(); }
	catch (ParseError error) { return NULL; }
}

Expr* Parser::expression() { return ternary(); }

Expr* Parser::ternary() {
	Expr* condition = equality();
	while (match(vector<TokenType>{ QUEST })) {
		Expr* ifTrue;
		Expr* ifFalse;
		ifTrue = expression();
		if (!match(vector{ COLON })) {
			advance(); // get to the EoF
			throw error(previous(), "Expect '?' to have matching ':'.");
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

	if (match(vector<TokenType>{LEFT_PAREN})) {
		Expr* expressionVar = expression();
		consume(RIGHT_PAREN, "Expect ')' after expression.");
		return new Grouping(expressionVar);
	}
	throw error(peek(), "Expected expression ");
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

Token Parser::advance() {
	if (!isAtEnd())
		current++;
	return previous();
}

bool Parser::isAtEnd() { return peek().type == EOF; }

Token Parser::peek() { return tokens[current]; }

Token Parser::previous() { return tokens[current - 1]; }

Token Parser::consume(TokenType type, string message) {
	if (check(type)) return advance();

	throw error(peek(), message);
}

// errors
ParseError Parser::error(Token token, string message) {
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