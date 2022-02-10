#pragma once
#include "../include.h"
#include "../parser/Expr.hpp"
#include "../mylox.h"
#include "LoxType.h"

class Interpreter : Visitor {
	LoxType result;
	Token curToken; // for error reporting
	void evaluate(Expr* expression);

	void visitTernary(const Ternary* expression) override;
	void visitBinary(const Binary* expression) override;
	void visitGrouping(const Grouping* expression) override;
	void visitLiteral(const Literal* expression) override;
	void visitUnary(const Unary* expression) override;

public:
	Interpreter();
	void interpret(Expr* expression);
	LoxType getResult();
};
