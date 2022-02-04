#pragma once
#include "include.h"
#include "tools/LoxError.h"
#include "scanner/Scanner.h"
#include "parser/Parser.h"
#include "tools/tools.h"
#include "scanner/Token.h"

void runPrompt();
void runFile(char* filepath);
void run(string& source);
void printTokens(vector<Token>& vec);
template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec);

//__declspec(selectany) LoxError* err;