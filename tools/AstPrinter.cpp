#include "AstPrinter.h"

void AstPrinter::read(Expr* expression) {
	expression->accept(this);
}

void AstPrinter::visitTernary(const Ternary* expression) {
	parenthesize(
		"?:",
		vector{ expression->condition, 
		expression->ifTrue, expression->ifTrue }
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
void AstPrinter::visitLiteral(const Literal* expression) {
	if (expression->value.isnil()) result += "nil";
	else result += expression->value.toString();
}
void AstPrinter::visitUnary(const Unary* expression) {
	parenthesize(expression->op.lexeme, vector{ expression->right });
}
void AstPrinter::visitVariable(const Variable* expression) {
	parenthesize(expression->name.lexeme, {});
}

string AstPrinter::parenthesize(string name, vector<Expr*> expressions) {
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