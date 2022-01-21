#pragma once
#include <string>
#include <vector>
#include "Token.h"
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
	void addString();
	void addNumber();
	void addIdentifier();
	void addToken(tokenType type, Literal lit = NULL);
};

