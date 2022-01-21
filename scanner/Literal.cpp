#include "Literal.h"

Literal::Literal(string str)
	: value{ str } {}
Literal::Literal(double dbl)
	: value{ dbl } {}

string Literal::toString() {
	if (std::holds_alternative<string>(value))
		return std::get<string>(value);
	else if (std::holds_alternative<double>(value))
		return std::to_string(std::get<double>(value));
	else
		return "unrecognized type";
}

//std::ostream& operator<<(std::ostream& os, const Literal& lit) {
//	if (std::holds_alternative<string>(lit.value))
//		os << std::get<string>(lit.value);
//	else if (std::holds_alternative<double>(lit.value))
//		os << std::to_string(std::get<double>(lit.value));
//}
