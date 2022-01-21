#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;

int runTool(vector<string> args);
void generateAst(vector<string> args);
void defineAst(string outputDir, string base, vector<string> types);
std::wstring ExePath();