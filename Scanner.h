#pragma once
#include "Token.h"
//#include "tokenType.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct Scanner {
	string source;
	vector<Token> tokens;
	int start, current, line;

	Scanner(string source);
	vector<Token> scanTokens();
	void scanToken();
	int isDone();
	char next();
	char peek();
	char peekNext();
	bool nextChar(char c);
	void collectString();
	void collectNumber();
	void addToken(tokenType type, Literal lit);
};

