#include "RPNPrinter.h"
void RPNPrinter::read(Expr* expression) {
	expression->accept(this);
}

void RPNPrinter::visitAssign(const Assign* expr) {
	collect("=", { new Variable{expr->name}, expr->value });
}
void RPNPrinter::visitBinary(const Binary* expression) {
	collect(
		expression->op.lexeme,
		vector{ expression->left, expression->right }
	);
}
void RPNPrinter::visitCall(const Call* expr) {
	collect("()", { expr->callee }); // FIXME needs to use expr->paren?
}
void RPNPrinter::visitGrouping(const Grouping* expression) {
	expression->expression->accept(this);
}
void RPNPrinter::visitLiteral(const Literal* expression) {
	if (expression->value.isnil()) result += "nil";
	else result += expression->value.toString();
}
void RPNPrinter::visitLogical(const Logical* expression) {
	collect(
		expression->op.lexeme,
		vector{ expression->left, expression->right }
	);
}
void RPNPrinter::visitTernary(const Ternary* expression) {
	expression->condition->accept(this);
	collect(
		"? " + getResult(),
		vector{ expression->ifTrue, expression->ifFalse }
	);
}
void RPNPrinter::visitUnary(const Unary* expression) {
	collect((expression->op.type == BANG) ? "not" : "neg",
		vector{ expression->right });
}
void RPNPrinter::visitVariable(const Variable* expr) {
	collect(expr->name.lexeme, {});
}

string RPNPrinter::collect(string name, vector<Expr*> expressions) {
	auto cur = expressions.begin();
	auto end = expressions.end();
	while (cur != end) {
		if (result.length() and
			result[result.length() - 1] != ' ')
			result += " ";
		(*cur)->accept(this);
		cur++;
	}
	result += " " + name;
	return result;
}

string RPNPrinter::getResult() { return result; }