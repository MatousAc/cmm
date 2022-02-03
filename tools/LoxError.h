#pragma once
#include "../include.h"
#include "../scanner/Token.h"
class LoxError {
public:
	bool hadError;

	LoxError();

	void report(int line, string msg, string where = "");
	void error(Token token, string message);
 };