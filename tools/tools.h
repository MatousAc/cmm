#pragma once
#include "../include.h"
#include "../scanner/Token.h"

int runTool(vector<string> args);
void testAstPrinter();
void trim(string& str);
vector<string> split(string str, string token);
string toLower(string str);
string repeat(string str, const size_t n);
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
void printTokens(vector<Token>& vec);

