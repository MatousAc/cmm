#pragma once
#include "../include.h"
#include "../scanner/Token.h"

int runTool(vector<string> args);
void testAstPrinter();
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);
void printTokens(vector<Token>& vec);

