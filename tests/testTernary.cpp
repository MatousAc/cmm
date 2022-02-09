#include "testTernary.h"

void testTernary(vector<string> args) {
	bool verbose = false;
	auto argc = args.size();
	if (argc > 3 && args[3] == "-verbose")
		verbose = true;
	vector<string> input = {
		// Prof. O.'s tests
		"1 ? 2 : 3",
		"0 ? 1 : 2",
		"!true ? \"hello\" : \"bye\"",
		"!false ? \"hello\" : \"bye\"",
		"true ? 5 : 7",
		"nil ? false : true",
		"1 == 1 ? 2 > 1 ? \"two\" : \"one\" : \"zero\"",
		"1 == 1 ? 2 < 1 ? \"two\" : \"one\" : \"zero\"",
		"1 != 1 ? 2 < 1 ? \"two\" : \"one\" : \"zero\"",
		"1 + 1 ? 2 + 2"
		// my tests
	};
	vector<string> expected = {
		// Prof. O.'s tests
		"2",
		"1",
		"bye",
		"hello",
		"5",
		"true",
		"two",
		"one",
		"zero",
		"[line 1] Error at end : Expect '?' to have matching ':'."
		// my tests
	};
	string actual;
	for (int i = 0; i < input.size(); i++) {
		actual = runLineTernary(input[i]);
		if (verbose) {
			cout << input[i] << "\nshould be: "
				<< expected[i] << "\nand is: "
				<< actual << endl;
			cout << ((actual != expected[i]) ? "FAIL\n" : "PASS\n");
		} else if (actual != expected[i])
			cout << actual << "\nshould be: "
			<< expected[i] << "\nFAIL";
	}
}

string runLineTernary(string& source) {
	Scanner scanner(source);
	vector<Token> tokens = scanner.scanTokens();
	Parser parser{ tokens };
	Expression* expression = parser.parse();

	// interpreting
	Interpreter* interpreter = new Interpreter;
	interpreter->interpret(expression);
	return interpreter->getResult().toString();
}