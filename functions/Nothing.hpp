#pragma once
#include "../interpreter/LoxCallable.h"

struct Nothing : LoxCallable {
	int arity() override { return 0; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		return LoxType{}; // the nothing type
	}
	string toString() { return "Nothing()"; }
	Nothing() {};
};

struct ExitFx : LoxCallable {
	int arity() override { return 0; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		throw ExitExcept{};
		return LoxType{};
	}
	string toString() { return "exit()"; }
	ExitFx() {};
};