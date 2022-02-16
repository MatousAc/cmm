#include "tools.h"
#include "generator.h"
#include "AstPrinter.h"
#include "../tests/testStrComp.h"
#include "../tests/testRPN.h"
#include "../tests/testTernary.h"

int runTool(vector<string> args) {
	auto argc = args.size();
	if (argc < 3) {
		printf("choose tool to run");
		return 0;
	}
	if (args[2] == "generator")
		generator(args);
	else if (args[2] == "AstPrinter")
		testAstPrinter();
	else if (args[2] == "testRPN")
		testRPN(args);
	else if (args[2] == "testTernary")
		testTernary(args);
	else if (args[2] == "testStrComp")
		testStrComp();
	else
		printf("no such tool");
	return 0;
}

void testAstPrinter() {
	Token min(MINUS, "-", NULL, 1);
	Token star(STAR, "*", NULL, 1);
	Grouping grp = new Binary(
		new Unary(min, new Literal(LoxType{ 123.0 })),
		star,
		new Grouping(new Literal(LoxType{ 45.67 })));

	AstPrinter pp;
	pp.read(&grp);
	cout << pp.getResult() << std::endl;
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

// prints a vector of tokens
void printTokens(vector<Token>& vec) {
	if (!vec.empty()) {
		auto iter = vec.begin();
		auto end = vec.end();
		printf("l: type\t| lexeme \tliteral\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		cout << (*iter++).display() << endl;
		while (iter != end)
			cout << (*iter++).display() << endl;
	}
}