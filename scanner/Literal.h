#pragma once
#include "../include.h"
#include "../interpreter/LoxType.h"
struct Literal {
	variant<string, double> value;
	Literal(string str);
	Literal(double dbl);
	bool empty() const;
	string toString() const;
	LoxType retrieve() const;
};

