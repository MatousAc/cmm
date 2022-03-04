#pragma once
#include "../include.h"
#include "LoxType.h"
#include "Interpreter.h"

class LoxCallable {
public:
	virtual int arity() = 0;
	virtual LoxType call(Interpreter* interpreter, vector<LoxType> arguments) = 0;
	virtual string toString() = 0;
};

//class LoxCallable {
//public:
//	virtual int arity() { return NULL; };
//	virtual LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {
//		return LoxType{};
//	};
//	virtual string toString() { return "LoxCallable"; };
//	LoxCallable() {};
//	explicit LoxCallable(LoxType val) {
//		if (val.type() == "LoxCallable")
//			LoxCallable{}; // confused
//	}
//};
// no need to use getResult() here because we know a function must return
// a LoxType (even if that is nil)
