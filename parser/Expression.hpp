#pragma once
#include "../scanner/Token.h"

struct Lit;
struct Visitor;

struct Expression {
    virtual ~Expression() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct Lit : Expression {
    Literal value;

    Lit(Literal value)
        :value{ value } {}

    void accept(Visitor* visitor) { visitor->visitLit(this); }
};

struct Visitor {
    void visitLit(const Lit* expression);
};