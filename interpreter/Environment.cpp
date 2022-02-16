#include "Environment.h"

Environment::Environment() 
	: values{} {}

void Environment::define(Token name, LoxType value) {
	values[name.lexeme] = value;
}

void Environment::assign(Token name, LoxType value) {
	if (values.find(name.lexeme) == values.end())
		throw new RunError(name,
			"Undefined variable '" + name.lexeme + "'.");
	values[name.lexeme] = value;
}

LoxType Environment::get(Token name) {
	if (values.find(name.lexeme) == values.end())
		throw new RunError(name,
			"Undefined variable '" + name.lexeme + "'.");
	return values[name.lexeme];
}