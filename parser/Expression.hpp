#pragma once
#include "../scanner/Token.h"

struct Ternary;
struct Binary;
struct Grouping;
struct Lit;
struct Unary;

struct Visitor {
    virtual void visitTernary(const Ternary* expression) = 0;
    virtual void visitBinary(const Binary* expression) = 0;
    virtual void visitGrouping(const Grouping* expression) = 0;
    virtual void visitLit(const Lit* expression) = 0;
    virtual void visitUnary(const Unary* expression) = 0;
};

struct Expression {
    virtual ~Expression() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct Ternary : Expression {
    Expression* condition;
    Expression* ifTrue;
    Expression* ifFalse;

    Ternary(Expression* condition, Expression* ifTrue, Expression* ifFalse)
        :condition{ condition }, ifTrue{ ifTrue }, ifFalse{ ifFalse } {}

    void accept(Visitor* visitor) override {
        visitor->visitTernary(this);
    }
};

struct Binary : Expression {
    Expression* left;
    Token op;
    Expression* right;

    Binary(Expression* left, Token op, Expression* right)
        :left{ left }, op{ op }, right{ right } {}

    void accept(Visitor* visitor) override {
        visitor->visitBinary(this);
    }
};

struct Grouping : Expression {
    Expression* expression;

    Grouping(Expression* expression)
        :expression{ expression } {}

    void accept(Visitor* visitor) override {
        visitor->visitGrouping(this);
    }
};

struct Lit : Expression {
    LoxType value;

    Lit(LoxType value)
        :value{ value } {}

    void accept(Visitor* visitor) override {
        visitor->visitLit(this);
    }
};

struct Unary : Expression {
    Token op;
    Expression* right;

    Unary(Token op, Expression* right)
        :op{ op }, right{ right } {}

    void accept(Visitor* visitor) override {
        visitor->visitUnary(this);
    }
};

