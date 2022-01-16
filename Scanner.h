#pragma once
#include "Token.h"
//#include "tokenType.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class Scanner {
	string source;
	vector<Token> tokens;
	int start, current, line;

	Scanner(string source);
	vector<Token> scanTokens();
	void scanToken();
	int isDone();
	char next();
	char peek();
	bool nextChar(char c);
	void addToken(tokenType type, string literal);
};

