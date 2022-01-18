#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Token.h"
using std::string;
using std::vector;
using std::unordered_map;

struct Scanner {
	string source;
	vector<Token> tokens;
	int start, current, line;
	// make the below static?
	unordered_map<string, tokenType> keywords;

	Scanner(string source);
	vector<Token> scanTokens();
	void scanToken();
	int isDone();
	char next();
	char peek();
	char peekNext();
	bool nextChar(char c);
	void traverseString();
	void traverseNumber();
	void addIdentifier();
	void addToken(tokenType type, Literal lit = NULL);
};

