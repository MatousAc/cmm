#include "Interpreter.h"

Interpreter::Interpreter() : result{} {};

void Interpreter::evaluate(Expression* expression) {
	expression->accept(this);
}

void Interpreter::visitBinary(const Binary* expression) {

}
void Interpreter::visitGrouping(const Grouping* expression) {
	evaluate(expression->expression);
}
void Interpreter::visitLit(const Lit* expression) {
	result = expression->value.retrieve();
}
void Interpreter::visitUnary(const Unary* expression) {
	evaluate(expression->right);
	LoxType right = getResult();

	switch (expression->op.type) {
	case MINUS:
		result = -right;
	case BANG:
		result = !right;
	default:
		break;
	}
}