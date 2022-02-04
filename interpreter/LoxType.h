#pragma once
#include "../include.h"
#include "../tools/tools.h"
#define DOUBLE_PRECISION 1e-7

struct LoxType {
	variant<string, double, bool> value;
	LoxType(string str);
	LoxType(double dbl);
	LoxType(bool bl);
	LoxType();
	bool empty() const;
	string toString() const;
	string numToLoxStr() const;

	// operator overloads
	bool operator==(const LoxType& r);
	bool operator!=(const LoxType& r);
	bool operator>(const LoxType& r);
	bool operator>=(const LoxType& r);
	bool operator<(const LoxType& r);
	bool operator<=(const LoxType& r);

	LoxType operator+(const LoxType& r);
	LoxType operator-(const LoxType& r);
	LoxType operator*(const LoxType& r);
	LoxType operator/(const LoxType& r);
	
	LoxType operator-();
	LoxType operator!();
};
