#pragma once
#include "../include.h"
#include "../parser/Expr.hpp"

class RPNPrinter : ExprVisitor {
	string result;
public:
	RPNPrinter() : result{} {};
	void read(Expr* expression);

	void visitAssign(const Assign* expr) override;
	void visitBinary(const Binary* expr) override;
	void visitCall(const Call* expr) override;
	void visitGrouping(const Grouping* expr) override;
	void visitLiteral(const Literal* expr) override;
	void visitLogical(const Logical* expr) override;
	void visitTernary(const Ternary* expr) override;
	void visitUnary(const Unary* expr) override;
	void visitVariable(const Variable* expr) override;

	string collect(string name, vector<Expr*> expressions);

	string getResult();
};

