#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unordered_map>
#include <vector>
#include "Scanner.h"
#include "Token.h"
using namespace std;

void runPrompt();
void runFile(char* filepath);
void run(string& source);
void error(int line, string msg, string where = "");
void printTokens(vector<Token>& vec);
// __delspec used to avoid linker error
__declspec(selectany) unordered_map<string, tokenType> keywords;