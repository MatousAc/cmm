#pragma once
#include "../include.h"
#include "tools.h" // for trim|split helpers

inline const string TAB = "    ";
inline const string TABx2 = TAB + TAB;

void generator(vector<string> args);
void writeSyntax(string outputDir, string base, string include, vector<string> types);
string buildBase(string base);
string buildProtoStructs(vector<string> names);
string buildStruct(string base, string name, vector<string> fields);
string buildVisitorStruct(string base, vector<string> types);