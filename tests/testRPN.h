#pragma once
#include "../include.h"
#include "../tools/LoxError.h"
#include "../scanner/Scanner.h"
#include "../parser/Parser.h"
#include "../tools/tools.h"
#include "../scanner/Token.h"
#include "../interpreter/Interpreter.h"
#include "../tools/RPNPrinter.h"

void testRPN(vector<string> args);

string runLineRPN(string& source);