#include "cmm.h"
#include "tools/tools.h"
#include "tools/LoxError.h"
#include "scanner/Token.h"
#include "scanner/Scanner.h"
#include "tools/AstPrinter.h"
#include "interpreter/Interpreter.h"

int main(int argc, char* argv[]) {
	// running tools
	vector<string> args{};
	for (int i{ 0 }; i < argc; i++) {
		args.push_back(argv[i]);
	};

	if (argc > 1) {
		if (args[1] == "-t") {
			runTool(args);
			return 0;
		} else if (args[1] == "-h") {
			runHelp();
			return 0;
		}
	};

	if (argc <= 1)
		runPrompt();
	else if (argc > 2)
		printf("invalid # of args\n");
	else
		runFile(argv[1]);
	return 0;
}

void runPrompt() {
	string line;
	while (true) {
		cout << "> ";
		getline(cin, line, '\n');
		if (line == "")
			err->report(1, "Expect expression.", "end");
		// czech if just expression
		exprToPrint(line);

		int code = run(line);
		switch (code) {
		case 65:
			// keep going
			err->hadError = false;
			break;
		case 70:
			exit(70);
			break;
		default:
			break;
		}
	}
}

void runFile(const char* filepath) {
	// run and czech for errors
	string program = readFile(filepath);
	int code = run(program);
	switch (code) {
	case 65:
		exit(65);
		break;
	case 70:
		exit(70);
		break;
	default:
		break;
	}
	if (err->hadError) return;
}

int run(string& source) {
	Scanner scanner(source); // scan into tokens
	vector<Token> tokens = scanner.scanTokens();
	Parser parser{ tokens }; // parse into AST
	vector<Stmt*> statements = parser.parse();

	// return codes for handling based on REPL/file exe
	if (err->hadError) return 65;
	if (err->hadRunError) return 70;

	// interpret code
	try {
		interpreter->interpret(statements);
	} catch (ExitExcept ex) {} // nothing to do
	return 0;
}
