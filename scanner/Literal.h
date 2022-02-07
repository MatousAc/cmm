#pragma once
#include "../include.h"
#include "../interpreter/LoxType.h"
#define DOUBLE_PRECISION 1e-7

struct Literal {
	variant<string, double> value;
	Literal(string str);
	Literal(double dbl);
	bool empty() const;
	string toString() const;
	string numToString() const;
	LoxType retrieve() const;
};

