#include "Environment.h"

Environment::Environment(Environment* enclosing)
	: values{},
	enclosing{ enclosing } {}

void Environment::define(Token name, LoxType value) {
	values[name.lexeme] = value;
}

void Environment::assign(Token name, LoxType value) {
	if (values.find(name.lexeme) != values.end()) {
		values[name.lexeme] = value;
		return;
	}

	if (enclosing != nullptr) {
		enclosing->assign(name, value);
		return;
	}

	throw new RunError(name,
		"Undefined variable '" + name.lexeme + "'.");
}

LoxType Environment::get(Token name) {
	// search in current scope
	if (values.find(name.lexeme) != values.end())
		return values[name.lexeme];
	// search in enclosing scope
	if (enclosing != nullptr)
		return enclosing->get(name);

	throw new RunError(name,
		"Undefined variable '" + name.lexeme + "'.");
}