#pragma once
#include <string>
#include "../interpreter/LoxCallable.h"

struct Length : LoxCallable {
	int arity() override { return 1; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		LoxType val = arguments[0];
		if (val.type() != "string") throw RunError(
			interpreter->curToken, // line number reporting
			"length only takes one string as it's argument"); //msg
		string str = get<string>(val.value);
		return LoxType{ (double)str.length() };
	}
	string toString() { return "length(string)"; }
	Length() {};
};

struct ParseNum : LoxCallable {
	int arity() override { return 1; }
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
		LoxType val = arguments[0];
		if (val.type() != "string") throw RunError(
			interpreter->curToken,
			"parseNum only takes one string as it's argument");
		return LoxType{ std::stod(get<string>(val.value)) };
	}
	string toString() { return "parseNum(string)"; }
	ParseNum() {};
};