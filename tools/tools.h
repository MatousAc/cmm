#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;

int runTool(vector<string> args);
void generateAst(vector<string> args);
void genAst(string outputDir, string base, vector<string> types);
void trim(string str);
string genStruct(string base, string structname, string members);
//std::wstring ExePath();