#pragma once
#include "../include.h"
#define DOUBLE_PRECISION 1e-7

struct LoxType {
	variant<string, double, bool, monostate> value;
	LoxType(string str);
	LoxType(double dbl);
	LoxType(bool bl);
	LoxType();
	bool isnil() const;
	bool isTruthy() const;
	string type() const;
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
	bool operator!();
};
