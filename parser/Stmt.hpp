#pragma once
#include "Expr.hpp"

struct Expression;
struct Print;
struct Var;

struct StmtVisitor {
    virtual void visitExpression(const Expression* stmt) = 0;
    virtual void visitPrint(const Print* stmt) = 0;
    virtual void visitVar(const Var* stmt) = 0;
};

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor* visitor) = 0;
};

struct Expression : Stmt {
    Expr* expression;

    Expression(Expr* expression)
        :expression{ expression } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitExpression(this);
    }
};

struct Print : Stmt {
    Expr* expression;

    Print(Expr* expression)
        :expression{ expression } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitPrint(this);
    }
};

struct Var : Stmt {
    Token name;
    Expr* initializer;

    Var(Token name, Expr* initializer)
        :name{ name }, initializer{ initializer } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitVar(this);
    }
};

