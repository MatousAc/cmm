#include "Environment.h"

Environment::Environment() 
	: values{} {}

void Environment::define(string name, LoxType value) {
	values[name] = value;
}

LoxType Environment::get(Token name) {
	if (values.find(name.lexeme) == values.end())
		throw new RunError(name,
			"Undefined variable '" + name.lexeme + "'.");
	return values[name.lexeme];
}