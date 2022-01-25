#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "genAst.h"
#include "prettyPrinter.h"
using std::string;
using std::vector;
using std::cout;

int runTool(vector<string> args);
void trim(string& str);
vector<string> split(string str, string token);
string toLower(string str);
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
