#pragma once
#include ".. /scanner/Token.h"
struct Expression {}
struct Binary : Expression {
	Expr left;
	Token op;
	Expr right;

Binary(Expr left, Token op, Expr right)
		:left{ left }, op{ op }, right{ right } {}
};
struct Grouping : Expression {
	Expr expression;

Grouping(Expr expression)
		:expression{ expression } {}
};
struct Literal : Expression {
	Literal value;

Literal(Literal value)
		:value{ value } {}
};
struct Unary : Expression {
	Token op;
	Expr right;

Unary(Token op, Expr right)
		:op{ op }, right{ right } {}
};
