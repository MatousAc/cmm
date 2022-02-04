#pragma once
#include "../include.h"
#include "../parser/Expression.hpp"
//#include "../mylox.h"
#include "LoxType.h"

class Interpreter : Visitor {
	LoxType result;
    Token curToken; // for error reporting
    void interpret(Expression* expression);
    void evaluate(Expression* expression);

    void visitBinary(const Binary* expression) override;
    void visitGrouping(const Grouping* expression) override;
    void visitLit(const Lit* expression) override;
    void visitUnary(const Unary* expression) override;
public:
	Interpreter();

	LoxType getResult();
};
