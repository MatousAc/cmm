#pragma once
#include <string>
#include <variant>
using std::string;
using std::variant;
struct Literal {
	variant<string, double> value;
	Literal(string str);
	Literal(double dbl);
	string toString();
};

