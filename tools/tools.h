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
void generateAst(vector<string> args);
void writeAst(string outputDir, string base, vector<string> types);
string buildStruct(string base, string structname, string contents);
void trim(string& str);
vector<string> split(string str, string token);
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
