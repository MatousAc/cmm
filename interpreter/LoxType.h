#pragma once
#include "../include.h"

struct LoxType {
	variant<string, double, bool> value;
	LoxType(string str);
	LoxType(double dbl);
	LoxType(bool bl);
	LoxType();
	string toString() const;
	bool empty() const;
	LoxType operator-();
};
