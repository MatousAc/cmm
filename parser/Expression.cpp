#pragma once
#include "../scanner/Token.h"
struct Expression {
    virtual ~Expression() = default;

    class Visitor {
    public:
        virtual void visitBinary(const Binary& expression) = 0;
        virtual void visitGrouping(const Grouping& expression) = 0;
        virtual void visitLit(const Lit& expression) = 0;
        virtual void visitUnary(const Unary& expression) = 0;
    };

    virtual void accept(Visitor&) const {}
};

struct Binary : Expression {
    Expression left;
    Token op;
    Expression right;

    Binary(Expression left, Token op, Expression right)
        :left{ left }, op{ op }, right{ right } {}

    void accept(Visitor& visitor) const override {
        visitor.visitBinary(*this);
    }
};

struct Grouping : Expression {
    Expression expression;

    Grouping(Expression expression)
        :expression{ expression } {}

    void accept(Visitor& visitor) const override {
        visitor.visitGrouping(*this);
    }
};

struct Lit : Expression {
    Literal value;

    Lit(Literal value)
        :value{ value } {}

    void accept(Visitor& visitor) const override {
        visitor.visitLit(*this);
    }
};

struct Unary : Expression {
    Token op;
    Expression right;

    Unary(Token op, Expression right)
        :op{ op }, right{ right } {}

    void accept(Visitor& visitor) const override {
        visitor.visitUnary(*this);
    }
};

