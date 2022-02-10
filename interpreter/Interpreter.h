#pragma once
#include "../include.h"
#include "../parser/Expr.hpp"
#include "../mylox.h"
#include "LoxType.h"

class Interpreter : ExprVisitor, StmtVisitor {
public:
	Interpreter();
	void interpret(vector<Stmt*> statements);
	LoxType getResult();
private:
	LoxType result;
	Token curToken; // for error reporting
	void execute(Stmt* stmt);
	void evaluate(Expr* expression);

	void visitExpression(const Expression* stmt) override;
	void visitPrint(const Print* stmt) override;

	void visitTernary(const Ternary* expression) override;
	void visitBinary(const Binary* expression) override;
	void visitGrouping(const Grouping* expression) override;
	void visitLiteral(const Literal* expression) override;
	void visitUnary(const Unary* expression) override;
};
