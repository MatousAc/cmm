#pragma once
#include "../include.h"
#include "Token.h"

class Scanner {
	string source;
	int start, current, line;

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
public:
	Scanner(string source);
	vector<Token> tokens;
	vector<Token> scanTokens();
};

