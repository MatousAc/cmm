#include "Environment.h"

Environment::Environment(Environment* enclosing)
	: values{},
	enclosing{ enclosing } {}

void Environment::define(Token name, LoxType value) {
	cout << "DEFINE\n";
	cout << name.lexeme << " = " << value.toString() << "\n";
	if (values.find(name.lexeme) != values.end())
		cout << "not found\n";
	values[name.lexeme] = value;
	cout << "value assigned: ";
	cout << values[name.lexeme].toString() << "\n";
}

void Environment::assign(Token name, LoxType value) {
	cout << "ASSIGN\n";
	if (values.find(name.lexeme) != values.end()) {
		cout << "local variable\n";
		values[name.lexeme] = value;
		return;
	}

	if (enclosing != nullptr) {
		cout << "going up an environment\n";
		enclosing->assign(name, value);
		return;
	}

	throw new RunError(name,
		"Undefined variable '" + name.lexeme + "'.");
}

LoxType Environment::get(Token name) {
	cout << "GET\n";
	// search in current scope
	if (values.find(name.lexeme) != values.end())
		return values[name.lexeme];
	// search in enclosing scope
	if (enclosing != nullptr)
		return enclosing->get(name);

	throw new RunError(name,
		"Undefined variable '" + name.lexeme + "'.");
}