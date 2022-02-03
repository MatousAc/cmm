#include "Interpreter.h"

Interpreter::Interpreter() : result{} {};

void Interpreter::evaluate(Expression* expression) {
	expression->accept(this);
}

void Interpreter::visitBinary(const Binary* expression) {
	evaluate(expression->left);
	LoxType left = getResult();
	evaluate(expression->right);
	LoxType right = getResult();

	switch (expression->op.type) {
	case MINUS:
		result = left - right;
		break;
	default:
		break;
	}
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
		break;
	case BANG:
		result = !right;
		break;
	default:
		break;
	}
}

LoxType Interpreter::getResult() {
	return result;
}