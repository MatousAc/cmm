#pragma once
#include "../include.h"
#include "../parser/Expression.hpp"

class RPNPrinter : Visitor {
	string result;
public:
	RPNPrinter() : result{} {};
	void read(Expression* expression);

	void visitTernary(const Ternary* expression) override;
	void visitBinary(const Binary* expression) override;
	void visitGrouping(const Grouping* expression) override;
	void visitLit(const Lit* expression) override;
	void visitUnary(const Unary* expression) override;

	string collect(string name, vector<Expression*> expressions);

	string getResult();
};

