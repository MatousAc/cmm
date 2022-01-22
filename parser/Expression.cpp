#pragma once
#include "Expression.h"
#include "../scanner/Token.h"
struct Expression {};

struct Binary : Expression {
	Expression left;
	Token op;
	Expression right;

	Binary(Expression left, Token op, Expression right)
		:left{ left }, op{ op }, right{ right } {}
};

