#include "LoxType.h"
#include "../tools/LoxError.h"
#include "../tools/tools.h"

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
	string res = "unknown type";
	if (empty())
		res = "nil";
	else if (holds_alternative<string>(value))
		res = get<string>(value);
	else if (holds_alternative<double>(value)) {
		res = this->numToLoxStr();
	} else if (holds_alternative<bool>(value)) {
		res = (get<bool>(value)) ? "true" : "false";
	}
	return res;
}
// helper
string LoxType::numToLoxStr() const {
	double dbl = get<double>(value);
	int integer = (int)dbl;
	string res;
	if ((dbl - integer) > DOUBLE_PRECISION)
		res = to_string(dbl);
	res = to_string(integer);
	return res;
}


///// ~~ operator overloads ~~ /////
// logical
// == : equals (different types cannpt be equal)
bool LoxType::operator==(const LoxType& r) {
	if (empty() && r.empty())
		return true;
	else if (empty() || r.empty())
		return false;
	// double == double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) == get<double>(r.value);
	// string == string
	else if (holds_alternative<string>(value) &&
		holds_alternative<string>(r.value))
		return get<string>(value).compare(get<string>(r.value)) == 0;
	else // type mismatch
		return false;
}
// !=
bool LoxType::operator!=(const LoxType& r) {
	return !((*this) == r);
}
// > : numerical && textual greater than
bool LoxType::operator>(const LoxType& r) {
	if (empty() || r.empty())
		return false;
	// double > double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) > get<double>(r.value);
	// string > string
	else if (holds_alternative<string>(value) &&
		holds_alternative<string>(r.value))
		return get<string>(value).compare(get<string>(r.value)) > 0;
	else // mismatched types
		err->runErrorMBT();
	return false;
}
// >=
bool LoxType::operator>=(const LoxType& r) {
	return *this > r || *this == r;
}
// < : num && text less than
bool LoxType::operator<(const LoxType& r) {
	if (empty() || r.empty())
		return false;
	// double > double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) < get<double>(r.value);
	// string > string
	else if (holds_alternative<string>(value) &&
		holds_alternative<string>(r.value))
		return get<string>(value).compare(get<string>(r.value)) < 0;
	else // mismatched types
		err->runErrorMBT();
	return false;
}
// <=
bool LoxType::operator<=(const LoxType& r) {
	return *this < r || *this == r;
}

// arithmetic
// + : addition, concatenation
LoxType LoxType::operator+(const LoxType& r) {
	if (empty()) // if this is empty
		return r;
	else if (r.empty())
		return this;
	// double + double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) + get<double>(r.value);
	// string + string
	else if (holds_alternative<string>(value) &&
		holds_alternative<string>(r.value))
		return get<string>(value) + get<string>(r.value);
	// string + toString(double)
	else if (holds_alternative<string>(value) &&
		holds_alternative<double>(r.value))
		return get<string>(value) + r.numToLoxStr();
	// toString(double) + string
	else if (holds_alternative<double>(value) &&
		holds_alternative<string>(r.value))
		return this->numToLoxStr() + get<string>(r.value);
	else // mismatched types
		err->runErrorMBT();
	return LoxType{};
}
// - : subtraction
LoxType LoxType::operator-(const LoxType& r) {
	if (empty()) // if this is empty
		return (-LoxType{ r });
	else if (r.empty())
		return this;
	// double - double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) - get<double>(r.value);
	else // mismatched types
		err->runErrorMBT();
	return LoxType{};
}
// * : multiplication and string duplication
LoxType LoxType::operator*(const LoxType& r) {
	if (empty() || r.empty()) // x * 0 = 0
		return LoxType{};
	// double * double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) * get<double>(r.value);
	// string * double
	else if (holds_alternative<string>(value) &&
		holds_alternative<double>(r.value))
		return repeat(get<string>(value), (size_t)get<double>(r.value));
	// double * string
	else if (holds_alternative<double>(value) &&
		holds_alternative<string>(r.value))
		return repeat(get<string>(r.value), (size_t)get<double>(value));
	else // mismatched types
		err->runErrorMBT();
	return LoxType{};
}
// / : division and line breaks
LoxType LoxType::operator/(const LoxType& r) {
	if (empty()) // if this is empty
		return LoxType{};
	else if (r.empty())
		throw RunError("division by nil");
	// double / double
	else if (holds_alternative<double>(value) &&
		holds_alternative<double>(r.value))
		return get<double>(value) / get<double>(r.value);
	// string / string
	else if (holds_alternative<string>(value) &&
		holds_alternative<string>(r.value))
		return get<string>(value) + "\n" + get<string>(r.value);
	else // mismatched types
		err->runErrorMBT();
	return LoxType{};
}

// unary
// - : negates numbers
LoxType LoxType::operator-() {
	if (holds_alternative<double>(value)) {
		return -(get<double>(value));
	} else // mismatched type
		err->runErrorMUT();
	return LoxType{};
}
// ! : works on numbers and bools
bool LoxType::operator!() {
	if (empty())
		return true;
	else if (holds_alternative<string>(value))
		return (get<string>(value).empty());
	else if (holds_alternative<double>(value))
		return !(get<double>(value));
	else if (holds_alternative<bool>(value))
		return !(get<bool>(value));
	else
		return false;
}
