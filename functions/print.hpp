#pragma once
#include "../interpreter/LoxCallable.h"

struct PrintFx : LoxCallable {
	int arity() override { return 1; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		for (LoxType arg : arguments)
			cout << arg.toString();
		return LoxType{};
	}
	string toString() { return "print(...)"; }
	PrintFx() {};
};

struct PrintLn : LoxCallable {
	int arity() override { return 1; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		for (LoxType arg : arguments)
			cout << arg.toString();
		cout << endl; // print newline
		return LoxType{};
	}
	string toString() { return "println(...)"; }
	PrintLn() {};
};