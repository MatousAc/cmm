#include "testStrComp.h"


void testStrComp() {
	vector<string> input = {
		"1 + 2",
		"(4 * \"hi\") == 12",
		"3 / 5 + 2 * (-2 - -5)",
		"\"two\" * (4 / 2)",
		"3 / 2 + 1 + -12",
		"true == false * 3",
		"2 - 3 + 4 / 3 * 8 + (3 + 4)",
		"4",
		"-34",
		"29 - 12 == 2 != 7 < 6",
		"4 + (1 - 2) != 24 > 3 - 4",
		"(\"sup\" + \" \") * 12",
		"9 / 5 == 3 * 7 / (9 - -2) != 7"
	};
	vector<string> expected = {
		"1 2 +",
		"4 hi * 12 ==",
		"3 5 / 2 2 - 5 - - * +",
		"two 4 2 / *",
		"3 2 / 1 + 12 - +",
		"1 0 3 * ==",
		"2 3 - 4 3 / 8 * + 3 4 + +",
		"4",
		"34 -",
		"29 12 - 2 == 7 6 < !=",
		"4 1 2 - + 24 3 4 - > !=",
		"sup   + 12 *",
		"9 5 / 3 7 * 9 2 - - / == 7 !="
	};
	string actual;
	for (int i = 0; i < input.size(); i++) {
		actual = interpretLineRPN(input[i]);
		if (actual != expected[i])
			cout << "_" << actual << "_"
			<< " ~should be~ "
			<< "_" << expected[i] << "_" << endl;
	}

}

string interpretLineRPN(string& source) {
	Scanner scanner(source);
	vector<Token> tokens = scanner.scanTokens();
	Parser parser{ tokens };
	Expression* expression = parser.parse();

	// interpreting
	Interpreter* interpreter = new Interpreter;
	interpreter->interpret(expression);
	return interpreter->getResult().toString();
}