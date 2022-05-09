#pragma once
#include <nlohmann/json.hpp>
#include "../include.h"
#include "../scanner/Token.h"

string exprToPrint(string& line);
int runTool(vector<string> args);
int profosTests();
void testREPL(auto test);
void testFile(auto test);
void runHelp();
// helpers
string readFile(const char* filepath);
void testAstPrinter();
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
void printTokens(vector<Token>& vec);

