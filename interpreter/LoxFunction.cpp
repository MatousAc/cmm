#include "LoxFunction.h"
#include "LoxType.h"

LoxFunction::LoxFunction(Function* declaration) 
	: declaration{ declaration } {}

int LoxFunction::arity() {
    return (int)declaration->params.size();
}

LoxType LoxFunction::call(Interpreter* interpreter, 
    vector<LoxType> arguments) {
    Environment* environment = new Environment(interpreter->globals);
    for (int i = 0; i < declaration->params.size(); i++) {
        environment->define(declaration->params[i].lexeme,
            arguments[i]);
    }

    interpreter->executeBlock(declaration->body, environment);
    return LoxType{};
}

string LoxFunction::toString() {
    return "<fn " + declaration->name.lexeme + ">";
}
