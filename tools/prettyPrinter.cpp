#include "prettyPrinter.h"

void PrettyPrinter::visitLit(const Lit* expression) {
    if (expression->value.empty()) result = "nil";
    else result = expression->value.toString();
}


//string prettyPrinter::paranthesise(const string& name,
//    std::initializer_list<const Expression*> expressions) {
//    return "";
//}
string PrettyPrinter::getResult() { return result; }