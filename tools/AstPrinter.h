#pragma once
#include "../include.h"
#include "../parser/Expression.hpp"

class AstPrinter : Visitor {
	string result;
public:
	AstPrinter() : result{} {};
	void read(Expression* expression);

	void visitTernary(const Ternary* expression) override;
	void visitBinary(const Binary* expression) override;
	void visitGrouping(const Grouping* expression) override;
	void visitLit(const Lit* expression) override;
	void visitUnary(const Unary* expression) override;

	string parenthesize(string name, vector<Expression*> expressions);

	string getResult();
};

