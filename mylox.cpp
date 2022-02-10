#include "mylox.h"

int main(int argc, char* argv[]) {
	// running tools
	vector<string> args{};
	for (int i{ 0 }; i < argc; i++) {
		args.push_back(argv[i]);
	};

	if ((argc > 1) and args[1] == "-t") {
		runTool(args);
		return 0;
	};

	// init err reporter
	err = new LoxError{};

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
		if (line == "") break;
		run(line);
		err->hadError = false;
	}
}

void runFile(char* filepath) {
	struct stat sb {};
	string program;
	FILE* file; // safely open a file
	errno_t error;
	if (((error = fopen_s(&file, filepath, "r")) != 0) ||
		(file == nullptr)) {
		cout << filepath << " could not be opened: " << file;
		return;
	}
	stat(filepath, &sb);
	program.resize(sb.st_size);
	fread(const_cast<char*>(program.data()), sb.st_size, 1, file);
	fclose(file);
	run(program);
	if (err->hadError) return;
}

void run(string& source) {
	Scanner scanner(source);
	vector<Token> tokens = scanner.scanTokens();
	Parser parser{ tokens };
	Expr* expression = parser.parse();

	if (err->hadError) exit(65);
	if (err->hadRunError) exit(70);
	
	// interpreting
	Interpreter* interpreter = new Interpreter;
	interpreter->interpret(expression);
	cout << interpreter->getResult().toString() << endl;
}

// prints a vector - Dr. Halterman
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << '{';
	if (!vec.empty()) {
		auto iter = vec.begin();
		auto end = vec.end();
		os << *iter++;
		while (iter != end)
			os << ", " << *iter++;
	}
	os << '}';
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