#include "AstPrinter.h"

void AstPrinter::read(Expression* expression) {
	expression->accept(this);
}

void AstPrinter::visitTernary(const Ternary* expression) {
	expression->condition->accept(this);
	parenthesize(
		getResult() + "?",
		vector{ expression->ifTrue, expression->ifTrue }
	);
}
void AstPrinter::visitBinary(const Binary* expression) {
	parenthesize(
		expression->op.lexeme,
		vector{ expression->left, expression->right }
	);
}
void AstPrinter::visitGrouping(const Grouping* expression) {
	parenthesize("group", vector{ expression->expression });
}
void AstPrinter::visitLit(const Lit* expression) {
	if (expression->value.isnil()) result += "nil";
	else result += expression->value.toString();
}
void AstPrinter::visitUnary(const Unary* expression) {
	parenthesize(expression->op.lexeme, vector{ expression->right });
}

string AstPrinter::parenthesize(string name, vector<Expression*> expressions) {
	result += "(" + name;
	auto cur = expressions.begin();
	auto end = expressions.end();
	while (cur != end) {
		result += " ";
		(*cur)->accept(this);
		cur++;
	}
	result += ")";
	return result;
}

string AstPrinter::getResult() { return result; }