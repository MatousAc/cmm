#include "Interpreter.h"
#include "../tools/LoxError.h"

Interpreter::Interpreter() : 
	result{}, 
	curToken{ EoF, "start", NULL, -1 } {};
void Interpreter::interpret(Expression* expression) {
	try {
		evaluate(expression);
		result = getResult();
		//cout << result.toString();
	}
	catch (RunError error) {
		err->handleRunError(RunError(curToken, error.message));
	}
}

void Interpreter::evaluate(Expression* expression) {
	expression->accept(this);
}

void Interpreter::visitBinary(const Binary* expression) {
	curToken = expression->op;
	evaluate(expression->left);
	LoxType left = getResult();
	evaluate(expression->right);
	LoxType right = getResult();

	switch (expression->op.type) {
	case EQUAL_EQUAL:
		result = left == right;
		break;
	case BANG_EQUAL:
		result = left != right;
		break;
	case GREATER:
		result = left > right;
		break;
	case GREATER_EQUAL:
		result = left >= right;
		break;
	case LESS:
		result = left < right;
		break;
	case LESS_EQUAL:
		result = left <= right;
		break;
	case PLUS:
		result = left + right;
		break;
	case MINUS:
		result = left - right;
		break;
	case STAR:
		result = left * right;
		break;
	case SLASH:
		result = left / right;
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
	curToken = expression->op;
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