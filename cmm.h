#pragma once
#include "include.h"
#include "parser/Parser.h"
#include <nlohmann/json.hpp>

void runPrompt();
void runFile(char* filepath);
int run(string& source);
