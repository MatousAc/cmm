#include "tools.h"
#include "helpers.h"
#include "generator.h"
#include "AstPrinter.h"
#include "../tests/testStrComp.h"
#include "../tests/testRPN.h"
#include "../tests/testTernary.h"
#include "../scanner/Scanner.h"
using namespace nlohmann;

void runHelp() {
	cout<< "Use:\t\tCommand Syntax\n"
		<< "----------------------------------------------\n"
		<< "Run REPL:\tcmm.exe\n"
		<< "Execute File:\tcmm.exe <filepath>\n"
		<< "Use Tool:\tcmm.exe -t <tool> <parameters>\n"
		<< "List Tools:\tcmm.exe -t\n";
}

int runTool(vector<string> args) {
	auto argc = args.size();
	if (argc < 3) {
		cout << "Choose from among the following tools:\n"
			<< "generator <destination dir>\n"
			<< "profosTests [-verbose]\n"
			<< "AstPrinter\n"
			<< "testRPN\n"
			<< "testTernary\n"
			<< "testStrComp]\n";
		return 0;
	}
	if (args[2] == "generator")
		generator(args);
	else if (args[2] == "profosTests")
		profosTests();
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

int profosTests() {
	//auto argc = args.size();
	//bool doVerbose = false; // verbose?
	//if (argc >= 4 && args[3] == "-verbose")
	//	doVerbose = true;

	// reading JSON test file
	//string str = readFile("../tests/tests.json");
	string str = readFile("../../tests/tests.json");
	json tests = json::parse(str)["tests"];
	for (auto test : tests) {
		string u = "______________________________";
		cout << u << test["name"] << u << endl;
		if (test["run"] == "./mylox") testREPL(test);
		else testFile(test);
	}
	return 0;
}

void testREPL(auto test) {
	vector<string> inputs = splitPure(test["input"], "\r\n");
	vector<string> outputs = splitPure(test["output"], "\r\n");
	int i = 0, size = inputs.size();
	while (i < size) {
		string input = inputs[i];
		string output = outputs[i];
		cout << "INPUT:\t\t\t" << input << endl;
		exprToPrint(input);
		cout << "EXPECTED OUTPUT:\t" << output << endl;
		cout << "ACTUAL OUTPUT:\t\t";
		run(input);
		cout << endl;
		i++;
		err->hadError = false;
		err->hadRunError = false;
	}
}

void testFile(auto test) {

}

string readFile(const char* filepath) {
	struct stat sb {};
	string contents;
	FILE* file; // safely open a file
	errno_t error;
	if (((error = fopen_s(&file, filepath, "r")) != 0) ||
		(file == nullptr)) {
		cout << filepath << " could not be opened: " << file;
		return "";
	}
	stat(filepath, &sb);
	contents.resize(sb.st_size);
	fread(const_cast<char*>(contents.data()), sb.st_size, 1, file);
	fclose(file);
	return contents;
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
// allows the repl to print expressions that are entered in
bool match(TokenType type, vector<TokenType> types) {
	auto curtype = types.begin();
	auto end = types.end();
	while (curtype != end) {
		if (type == *curtype)
			return true;
		curtype++;
	}
	return false;
}

bool isExpr(vector<Token> tokens) {
	auto begin = tokens.begin();
	auto end = tokens.end();
	auto last = end - 2;
	if (begin == end) return false;
	else if (match((*begin).type, {
		BREAK, CONTINUE, EXIT, PRINT,
		FOR, WHILE, LEFT_BRACE, EoF, IF, FUN
		})) {
		return false;
	} else if ((*last).type != SEMICOLON) {
		// doesn't begin with stmt keyword
		// && doesn't end in ';'
		return true;
	} else { // anything else does not qualify
		return false;
	}
}

string exprToPrint(string& line) {
	if (line == "") cout << ("[line 1] Error at end: Expect expression."); // FIXME
	Scanner scanner(line);
	vector<Token> tokens = scanner.scanTokens();
	if (isExpr(tokens)) {
		line = "print " + line + " ;";
	}
	return line;
}

