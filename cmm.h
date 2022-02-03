#pragma once
#include <sys/stat.h>
#include <fcntl.h>
#include "include.h"
#include <unordered_map>
#include "tools/LoxError.h"
#include "scanner/Scanner.h"
#include "parser/Parser.h"
#include "tools/tools.h"
using namespace std;

void runPrompt();
void runFile(char* filepath);
void run(string& source);
void printTokens(vector<Token>& vec);
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
// __delspec used to avoid linker error
__declspec(selectany) unordered_map<string, tokenType> keywords;
