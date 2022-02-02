#pragma once
#include "../include.h"
#include "tools.h" // for trim|split helpers

inline const string TAB = "    ";
inline const string TABx2 = TAB + TAB;

void genAst(vector<string> args);
void writeAst(string outputDir, string base, vector<string> types);
string buildBase(string base);
string buildProtoStructs(vector<string> names);
string buildStruct(string base, string name, vector<string> fields);
string buildVisitorStruct(string base, vector<string> types);