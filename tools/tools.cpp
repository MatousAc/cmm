#include "tools.h"

int runTool(vector<string> args) {
	auto argc = args.size();
	if (argc < 3) {
		printf("choose tool to run");
		return 0;
	}
	if (args[2] == "generateAst")
		genAst(args);
	else if (args[2] == "AstPrinter")
		testAstPrinter();
	else if (args[2] == "testRPN")
		testRPN();
	else
		printf("no such tool");
	return 0;
}

void testAstPrinter() {
	Token min(MINUS, "-", NULL, 1);
	Token star(STAR, "*", NULL, 1);
	Grouping grp = new Binary(
		new Unary(min, new Lit(123)),
		star,
		new Grouping(new Lit{ 45.67 }));

	AstPrinter pp;
	pp.read(&grp);
	cout << pp.getResult() << std::endl;
}

// adapted from DelftStack:
void trim(string& str) {
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
}

// adapted from Shiqi Ai on SO:
vector<string> split(string str, string token) {
	vector<string> result;
	while (str.size()) {
		auto index = str.find(token);
		string substr;
		if ((substr = str.substr(0, index)) == "") {
			str = str.substr(index + token.size());
		} else if (index != string::npos) {
			result.push_back(substr);
			str = str.substr(index + token.size());
		} else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

string toLower(string str) {
	for (int i = 0; i < str.length(); i++) {
		char c = str[i];
		if (c <= 'Z' && c >= 'A')
			str[i] -= ('Z' - 'z');
	}
	return str;
}

// from Daniel on SO
// repeats a string a number of times
string repeat(string str, const size_t n) {
	if (n == 0) {
		str.clear();
		str.shrink_to_fit();
		return str;
	} else if (n == 1 || str.empty()) {
		return str;
	}
	const auto period = str.size();
	if (period == 1) {
		str.append(n - 1, str.front());
		return str;
	}
	str.reserve(period * n);
	size_t m{ 2 };
	for (; m < n; m *= 2) str += str;
	str.append(str.c_str(), (n - (m / 2)) * period);
	return str;
}

// prints a vector - Dr. Halterman
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "\n{\n";
	if (!vec.empty()) {
		auto iter = vec.begin();
		auto end = vec.end();
		os << *iter++;
		while (iter != end)
			os << '\n' << *iter++;
	}
	os << "\n}\n";
	return os;
}