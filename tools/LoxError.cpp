#include "LoxError.h"

LoxError::LoxError() : hadError{ false } {};

void LoxError::report(int line, string msg, string where) {
    cout << "error on line " << line
        << " @ " << where << ": "
        << msg << endl;
    hadError = true;
}

void LoxError::error(Token token, string message) {
    if (token.type == EoF) {
        report(token.line, " at end", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}