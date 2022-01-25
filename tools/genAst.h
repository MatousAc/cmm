#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "tools.h"

using std::string;
using std::vector;
using std::cout;
inline const string TAB = "    ";

void genAst(vector<string> args);
void writeAst(string outputDir, string base, vector<string> types);
string buildProtoStructs(vector<string> names);
string buildVisitorClass(string base, vector<string> types);
string buildStruct(string base, string name, vector<string> fields);