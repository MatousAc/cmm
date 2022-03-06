#pragma once
#include "../include.h"
#include "LoxCallable.hpp"
#include "LoxFunction.h"
#define DOUBLE_PRECISION 1e-7

struct LoxType {
	variant<
		monostate,
		string, double, bool
		//LoxCallable*,
		//LoxFunction*
	> value;
	LoxType();
	LoxType(string str);
	LoxType(double dbl);
	LoxType(bool bl);
	//LoxType(LoxCallable* callable);
	//LoxType(LoxFunction* function);
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
