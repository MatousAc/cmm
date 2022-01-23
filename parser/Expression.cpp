#pragma once
#include "../scanner/Token.h"
struct Expression {};

struct Binary : Expression {
    Expression left;
    Token op;
    Expression right;

    Binary(Expression left, Token op, Expression right)
        :left{ left }, op{ op }, right{ right } {}
};

struct Grouping : Expression {
    Expression expression;

    Grouping(Expression expression)
        :expression{ expression } {}
};

struct Lit : Expression {
    Literal value;

    Lit(Literal value)
        :value{ value } {}
};

struct Unary : Expression {
    Token op;
    Expression right;

    Unary(Token op, Expression right)
        :op{ op }, right{ right } {}
};

