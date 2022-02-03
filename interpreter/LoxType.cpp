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
	if (holds_alternative<string>(value) ||
		(holds_alternative<double>(value)) ||
		(holds_alternative<bool>(value)))
		return false;
	else
		return true;
}

string LoxType::toString() const {
	if (holds_alternative<string>(value))
		return get<string>(value);
	else if (holds_alternative<double>(value)) {
		string res = std::to_string(get<double>(value));
		return res.substr(0, res.length() - 5);
	} else if (holds_alternative<bool>(value)) {
		bool res = get<bool>(value);
		return (res) ? "true" : "false";
	} else
		return "unrecognized type";
}

// operator overloads
// unary - overload: negates numbers
LoxType LoxType::operator-() {
	if (holds_alternative<double>(value)) {
		return -(get<double>(value));
	} else
		return this;
}

// ! op overload: works on numbers and bools
LoxType LoxType::operator!() {
	if (empty())
		return LoxType{ true };
	else if (holds_alternative<double>(value))
		return !(get<double>(value));
	else if (holds_alternative<bool>(value))
		return !(get<bool>(value));
	else
		return false;
}

// - overload
LoxType LoxType::operator+(const LoxType& right) {
	if (empty()) // if this is empty
		return right;
	else if (right.empty())
		return this;
	// double + double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(right.value))
		return get<double>(value) + get<double>(right.value);
	// string + string
	else if (holds_alternative<string>(value) &&
		holds_alternative<string>(right.value))
		return get<string>(value) + get<string>(right.value);
	// string + toString(double)
	else if (holds_alternative<string>(value) &&
		holds_alternative<double>(right.value))
		return get<string>(value) + to_string(get<double>(right.value));
	// toString(double) + string
	else if (holds_alternative<double>(value) &&
		holds_alternative<string>(right.value))
		return to_string(get<double>(value)) + get<string>(right.value);
	else // the second term
		return this;
}

LoxType LoxType::operator-(const LoxType& right) {
	if (empty()) // if this is empty
		return (-LoxType{ right });
	else if (right.empty())
		return this;
	// double - double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(right.value))
		return get<double>(value) - get<double>(right.value);
	else // for now ignore the second term
		return this;
}