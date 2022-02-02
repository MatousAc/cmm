#include "PrettyPrinter.h"

void PrettyPrinter::read(Expression* expression) {
    expression->accept(this);
}

void PrettyPrinter::visitBinary(const Binary* expression) {
    // result is built up as "this" is passed around:
    expression->left->accept(this);
    string left = result;
    expression->right->accept(this);
    string right = result;
    result = left + expression->op.lexeme + right;
}
void PrettyPrinter::visitGrouping(const Grouping* expression) {
    expression->expression->accept(this);
}

void PrettyPrinter::visitLit(const Lit* expression) {
    if (expression->value.empty()) result = "nil";
    else result = expression->value.toString();
}

void PrettyPrinter::visitUnary(const Unary* expression) {
    expression->right->accept(this);
    result = expression->op.lexeme + result;
}

//string prettyPrinter::paranthesise(const string& name,
//    std::initializer_list<const Expression*> expressions) {
//    return "";
//}
string PrettyPrinter::getResult() { return result; }