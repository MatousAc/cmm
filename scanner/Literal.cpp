#include "Literal.h"

Literal::Literal(string str)
	: value{ str } {}
Literal::Literal(double dbl)
	: value{ dbl } {}

bool Literal::empty() const {
	if (std::holds_alternative<string>(value) ||
		(std::holds_alternative<double>(value)))
		return false;
	else
		return true;
}

string Literal::toString() const {
	if (std::holds_alternative<string>(value))
		return std::get<string>(value);
	else if (std::holds_alternative<double>(value)) {
		string res = std::to_string(std::get<double>(value));
		return res.substr(0, res.length() - 5);
	} 	else
		return "unrecognized type";
}
