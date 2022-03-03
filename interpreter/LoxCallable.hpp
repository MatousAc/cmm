#pragma once
#include "../include.h"
#include "LoxType.h"
#include "Interpreter.h"

class LoxCallable {
public:
	virtual int arity() {};
	virtual LoxType call(Interpreter* interpreter, vector<LoxType> arguments) {};
}; 
// no need to use getResult() here because we know a function must return
// a LoxType (even if that is nil)
