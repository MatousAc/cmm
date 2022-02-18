#pragma once
#include "Expr.hpp"

struct Block;
struct Expression;
struct For;
struct If;
struct Print;
struct Var;
struct While;

struct StmtVisitor {
    virtual void visitBlock(const Block* stmt) = 0;
    virtual void visitExpression(const Expression* stmt) = 0;
    virtual void visitFor(const For* stmt) = 0;
    virtual void visitIf(const If* stmt) = 0;
    virtual void visitPrint(const Print* stmt) = 0;
    virtual void visitVar(const Var* stmt) = 0;
    virtual void visitWhile(const While* stmt) = 0;
};

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor* visitor) = 0;
};

struct Block : Stmt {
    vector<Stmt*> statements;

    Block(vector<Stmt*> statements)
        :statements{ statements } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitBlock(this);
    }
};

struct Expression : Stmt {
    Expr* expression;

    Expression(Expr* expression)
        :expression{ expression } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitExpression(this);
    }
};

struct For : Stmt {
    Stmt* initializer;
    Expr* condition;
    Expr* increment;
    Stmt* body;

    For(Stmt* initializer, Expr* condition, Expr* increment, Stmt* body)
        :initializer{ initializer }, condition{ condition }, increment{ increment }, body{ body } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitFor(this);
    }
};

struct If : Stmt {
    Expr* condition;
    Stmt* thenBranch;
    Stmt* elseBranch;

    If(Expr* condition, Stmt* thenBranch, Stmt* elseBranch)
        :condition{ condition }, thenBranch{ thenBranch }, elseBranch{ elseBranch } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitIf(this);
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

struct While : Stmt {
    Expr* condition;
    Stmt* body;

    While(Expr* condition, Stmt* body)
        :condition{ condition }, body{ body } {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitWhile(this);
    }
};

