#pragma once
#include <unordered_map>
#include "../include.h"
#include "../scanner/Token.h"
#include "LoxType.h"
#include "../tools/LoxError.h"
using std::unordered_map;

class Environment {
	unordered_map<string, LoxType> values;

public:
	Environment();
	void define(Token name, LoxType value);
	void assign(Token name, LoxType value);
	LoxType get(Token name);
};

