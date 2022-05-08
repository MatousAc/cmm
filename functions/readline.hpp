#pragma once
#include "../interpreter/LoxCallable.h"

struct ReadLine : LoxCallable {
	int arity() override { return 0; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		string str;
		std::getline(cin, str);
		LoxType input{str};
		return input;
	}
	string toString() { return "readline()"; }
	ReadLine() {};
};