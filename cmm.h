#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include "Scanner.h"
#include "Token.h"
using namespace std;

void runPrompt();
void runFile(string& filepath);
void run(string& source);
void error(int line, string msg, string where = "");