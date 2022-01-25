#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;
inline const string TAB = "    ";

int runTool(vector<string> args);
void genAst(vector<string> args);
void writeAst(string outputDir, string base, vector<string> types);
string buildVisitorClass(string base, vector<string> types);
string buildStruct(string base, string structname, string contents);
void trim(string& str);
vector<string> split(string str, string token);
string toLower(string str);
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
