#include "Literal.h"

Literal::Literal(string str)
	: value{ str } {}
Literal::Literal(double dbl)
	: value{ dbl } {}

bool Literal::empty() const {
	if (holds_alternative<string>(value) ||
		(holds_alternative<double>(value)))
		return false;
	else
		return true;
}

string Literal::toString() const {
	if (holds_alternative<string>(value))
		return get<string>(value);
	else if (holds_alternative<double>(value)) {
		string res = to_string(get<double>(value));
		return res.substr(0, res.length() - 5);
	} 	else
		return "unrecognized type";
}

LoxType Literal::retrieve() const {
	if (holds_alternative<string>(value))
		return LoxType{ get<string>(value) };
	else if (holds_alternative<double>(value))
		return LoxType{ get<double>(value) };
	else
		return LoxType{};
}