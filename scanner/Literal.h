#pragma once
#include "../include.h"
#include <variant>
using std::variant;

struct Literal {
	variant<string, double> value;
	Literal(string str);
	Literal(double dbl);
	string toString() const;
	bool empty() const;
};

