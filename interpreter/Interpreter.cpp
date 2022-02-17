#include "Interpreter.h"
#include "../tools/LoxError.h"

// public
Interpreter::Interpreter() :
	result{},
	environment{},
	curToken{ EoF, "start", NULL, -1 } {};
void Interpreter::interpret(vector<Stmt*> statements) {
	try {
		auto statement = statements.begin();
		auto end = statements.end();
		while (statement != end) {
			execute(*statement);
			result = getResult();
			statement++;
		}
	}
	catch (RunError error) {
		err->handleRunError(RunError(curToken, error.message));
	}
}

LoxType Interpreter::getResult() {
	return result;
}

// private
void Interpreter::execute(Stmt* stmt) {
	stmt->accept(this);
}

void Interpreter::evaluate(Expr* expression) {
	expression->accept(this);
}

void Interpreter::executeBlock(vector<Stmt*> statements, 
	Environment* environment) {
	Environment previous = this->environment;
	try {
		this->environment = environment;
		for (auto& statement : statements) {
			execute(statement);
		}
	}
	catch (runtime_error) {}
	this->environment = previous;
}

// visiting statements
void Interpreter::visitVar(const Var* stmt) {
	LoxType value{};
	if (stmt->initializer != NULL) {
		evaluate(stmt->initializer);
		value = getResult();
	}
	environment.define(stmt->name, value);
}

void Interpreter::visitExpression(const Expression* stmt) {
	evaluate(stmt->expression);
}

void Interpreter::visitIf(const If* stmt) {
	evaluate(stmt->condition); // eval cond
	if (getResult().isTruthy()) {
		execute(stmt->thenBranch);
	} else if (stmt->elseBranch != nullptr) {
		execute(stmt->elseBranch);
	}
}

void Interpreter::visitPrint(const Print* stmt) {
	evaluate(stmt->expression);
	LoxType value = getResult();
	cout << value.toString() << endl;
}

void Interpreter::visitBlock(const Block* stmt) {
	executeBlock(stmt->statements, new Environment(environment));
}

// visiting expressions
void Interpreter::visitAssign(const Assign* expression) {
	evaluate(expression->value);
	LoxType value = getResult();
	environment.assign(expression->name, value);
	result = value;
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
void Interpreter::visitLiteral(const Literal* expression) {
	result = expression->value;
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
void Interpreter::visitTernary(const Ternary* expression) {
	expression->condition->accept(this);
	if (getResult().isTruthy())
		expression->ifTrue->accept(this);
	else
		expression->ifFalse->accept(this);
}
void Interpreter::visitVariable(const Variable* expression) {
	result = environment.get(expression->name);
}
