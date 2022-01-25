#include "prettyPrinter.h"

string prettyPrinter::visitLit(const Lit& expression) {
    if (expression.value.empty()) return "nil";
    return expression.value.toString();
}


//string prettyPrinter::paranthesise(const string& name,
//    std::initializer_list<const Expression*> expressions) {
//    return "";
//}