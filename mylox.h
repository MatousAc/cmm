#pragma once
#include "include.h"
#include "tools/LoxError.h"
#include "scanner/Scanner.h"
#include "parser/Parser.h"
#include "tools/tools.h"
#include "scanner/Token.h"
#include "interpreter/Interpreter.h"

void runPrompt();
void runFile(char* filepath);
void run(string& source);
