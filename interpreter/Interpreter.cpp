// interprets the Abstract Syntax Tree
#include "Interpreter.h"
#include "../tools/LoxError.h"

// public
Interpreter::Interpreter() :
	result{},
	environment{ new Environment{} },
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

// private - execution helpers
void Interpreter::execute(Stmt* stmt) {
	stmt->accept(this);
}

void Interpreter::evaluate(Expr* expression) {
	expression->accept(this);
}

void Interpreter::executeBlock(vector<Stmt*> statements,
	Environment* environment) {
	Environment* previous = this->environment;
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
void Interpreter::visitBlock(const Block* statement) {
	executeBlock(statement->statements, new Environment(environment));
}
void Interpreter::visitExpression(const Expression* statement) {
	evaluate(statement->expression);
}
void Interpreter::visitFor(const For* statement) {
	if (statement->initializer != nullptr) // init
		execute(statement->initializer);
	// loop
	evaluate(statement->condition);
	while (getResult().isTruthy()) {
		execute(statement->body);
		if (statement->increment != nullptr)
			evaluate(statement->increment);
		evaluate(statement->condition);
	}
}
void Interpreter::visitIf(const If* statement) {
	evaluate(statement->condition); // eval cond
	if (getResult().isTruthy()) {
		execute(statement->thenBranch);
	} else if (statement->elseBranch != nullptr) {
		execute(statement->elseBranch);
	}
}
void Interpreter::visitPrint(const Print* statement) {
	evaluate(statement->expression);
	LoxType value = getResult();
	cout << value.toString() << endl;
}
void Interpreter::visitVar(const Var* statement) {
	LoxType value{};
	if (statement->initializer != NULL) {
		evaluate(statement->initializer);
		value = getResult();
	}
	environment->define(statement->name, value);
}
void Interpreter::visitWhile(const While* statement) {
	evaluate(statement->condition); // eval condition
	while (getResult().isTruthy()) { // czech condition
		execute(statement->body);
		evaluate(statement->condition);
	}
}

// visiting expressions
void Interpreter::visitAssign(const Assign* expression) {
	evaluate(expression->value);
	LoxType value = getResult();
	environment->assign(expression->name, value);
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
void Interpreter::visitLogical(const Logical* expression) {
	evaluate(expression->left);
	LoxType left = getResult();
	// FIXME can we simplify this?
	if (expression->op.type == OR) {
		if (left.isTruthy()) return;
	} else { // must be AND
		if (!left.isTruthy()) return;
	}
	evaluate(expression->right);
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
	result = environment->get(expression->name);
}
