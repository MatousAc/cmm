#pragma once
#include "../include.h"
#include "tools.h"

inline const string TAB = "    ";
inline const string TABx2 = TAB + TAB;
inline const string TABx3 = TABx2 + TAB;
inline const string TABx4 = TABx3 + TAB;
inline const string TABx5 = TABx4 + TAB;

void genAst(vector<string> args);
void writeAst(string outputDir, string base, vector<string> types);
string buildProtoStructs(vector<string> names);
string buildVisitorClass(string base, vector<string> types);
string buildStruct(string base, string name, vector<string> fields);