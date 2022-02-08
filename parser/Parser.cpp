#include "Parser.h"
#include "../tools/LoxError.h"

Expression* Parser::parse() {
	try { return expression(); }
	catch (ParseError error) { return NULL; }
}

Expression* Parser::expression() { return ternary(); }

Expression* Parser::ternary() {
	Expression* condition = equality();
	while (match(vector<TokenType>{ QUEST })) {
		Expression* ifTrue;
		Expression* ifFalse;
		ifTrue = ternary();
		Token token = previous();
		if (token.type != COLON)
			throw error(token, "expected \":\"");
		ifFalse = ternary();
		return new Ternary(condition, ifTrue, ifFalse);
	}
	return condition;
}


Expression* Parser::equality() {
	Expression* expression = comparison();

	while (match(vector<TokenType>{ BANG_EQUAL, EQUAL_EQUAL })) {
		Token op = previous();
		Expression* right = comparison();
		expression = new Binary(expression, op, right);
	}
	return expression;
}

Expression* Parser::comparison() {
	Expression* expr = term();

	while (match(vector<TokenType>{ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
		Token op = previous();
		Expression* right = term();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expression* Parser::term() {
	Expression* expression = factor();

	while (match(vector<TokenType>{ MINUS, PLUS })) {
		Token op = previous();
		Expression* right = factor();
		expression = new Binary(expression, op, right);
	}
	return expression;
}

Expression* Parser::factor() {
	Expression* expression = unary();

	while (match(vector<TokenType>{ SLASH, STAR })) {
		Token op = previous();
		Expression* right = unary();
		expression = new Binary(expression, op, right);
	}
	return expression;
}

Expression* Parser::unary() {
	if (match(vector<TokenType>{BANG, MINUS})) {
		Token op = previous();
		Expression* right = unary();
		return new Unary(op, right);
	}
	return primary();
}

Expression* Parser::primary() {
	if (match(vector<TokenType>{FALSE})) return new Lit(false);
	if (match(vector<TokenType>{TRUE})) return new Lit(true);
	if (match(vector<TokenType>{NIL})) return new Lit(NULL);

	if (match(vector<TokenType>{NUMBER, STRING})) {
		return new Lit(previous().lit);
	}

	if (match(vector<TokenType>{LEFT_PAREN})) {
		Expression* expressionVar = expression();
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