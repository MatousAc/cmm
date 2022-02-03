#include "LoxType.h"

// various constructors
LoxType::LoxType(string str)
	: value{ str } {}
LoxType::LoxType(double dbl)
	: value{ dbl } {}
LoxType::LoxType(bool bl)
	: value{ bl } {}
LoxType::LoxType()
	: value{} {}

// czechs if empty (contains NULL)
bool LoxType::empty() const {
	if (std::holds_alternative<string>(value) ||
		(std::holds_alternative<double>(value)) ||
		(std::holds_alternative<bool>(value)))
		return false;
	else
		return true;
}

string LoxType::toString() const {
	if (std::holds_alternative<string>(value))
		return std::get<string>(value);
	else if (std::holds_alternative<double>(value)) {
		string res = std::to_string(std::get<double>(value));
		return res.substr(0, res.length() - 5);
	} else if (std::holds_alternative<double>(value)) {
		bool res = std::get<bool>(value);
		return (res) ? "true" : "false";
	} else
		return "unrecognized type";
}

// unary operator overload
LoxType LoxType::operator-() {
	if (std::holds_alternative<double>(value)) {
		return -(std::get<double>(value));
	} else
		return this;
}