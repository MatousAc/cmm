#pragma once
#include "../include.h"
#include "../parser/Stmt.hpp"
#include "../interpreter/Interpreter.h"
#include "../interpreter/LoxCallable.h"

struct LoxFunction : LoxCallable {
	Function* declaration;
public:
	LoxFunction(Function* declaration);
	int arity() override;
	LoxType call(Interpreter* interpreter, vector<LoxType> arguments) override;
	string toString() override;
};
