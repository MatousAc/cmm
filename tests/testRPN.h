#pragma once
#include "../include.h"
#include "../scanner/Scanner.h"
#include "../parser/Parser.h"
#include "../tools/tools.h"
#include "../scanner/Token.h"
#include "../tools/RPNPrinter.h"

void testRPN();

string runLineRPN(string& source);