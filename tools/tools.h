#pragma once
#include "../include.h"
#include "genAst.h"
#include "PrettyPrinter.h"

int runTool(vector<string> args);
void testPrettyPrinter();
void trim(string& str);
vector<string> split(string str, string token);
string toLower(string str);
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
