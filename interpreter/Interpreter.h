#pragma once
#include "../include.h"
#include "../parser/Expr.hpp"
#include "../cmm.h"
#include "LoxType.h"
#include "Environment.h"

class Interpreter : ExprVisitor, StmtVisitor {
public:
	Interpreter();
	void interpret(vector<Stmt*> statements);
	LoxType getResult();
private:
	LoxType result;
	Environment* environment;
	Token curToken; // for error reporting

	void execute(Stmt* stmt);
	void evaluate(Expr* expression);
	void executeBlock(vector<Stmt*> statements, Environment* environment);

	void visitBlock(const Block* statement) override;
	void visitExpression(const Expression* statement) override;
	void visitFor(const For* statement) override;
	void visitIf(const If* statement) override;
	void visitPrint(const Print* statement) override;
	void visitVar(const Var* statement) override;
	void visitWhile(const While* statement) override;

	void visitAssign(const Assign* expression) override;
	void visitBinary(const Binary* expression) override;
	void visitGrouping(const Grouping* expression) override;
	void visitLogical(const Logical* expression) override;
	void visitLiteral(const Literal* expression) override;
	void visitUnary(const Unary* expression) override;
	void visitTernary(const Ternary* expression) override;
	void visitVariable(const Variable* expression) override;
};

// global, stateful interpreter
inline Interpreter* interpreter = new Interpreter;
