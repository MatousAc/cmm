#pragma once
#include "../include.h"
#include "../parser/Stmt.hpp"
#include "LoxCallable.hpp"

class LoxFunction : LoxCallable {
	Function declaration;
public:
	LoxFunction(Function declaration);
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments);
};

