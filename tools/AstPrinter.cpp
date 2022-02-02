#include "AstPrinter.h"

void AstPrinter::read(Expression* expression) {
    expression->accept(this);
}

void AstPrinter::visitBinary(const Binary* expression) {
    // result is built up as "this" is passed around:
    //expression->left->accept(this);
    //string left = result;
    //expression->right->accept(this);
    //string right = result;
    //result = left + expression->op.lexeme + right;
    parenthesize(
        expression->op.lexeme,
        vector{expression->left, expression->right}
    );
}
void AstPrinter::visitGrouping(const Grouping* expression) {
    //expression->expression->accept(this);
    parenthesize("group", vector{ expression->expression });
}

void AstPrinter::visitLit(const Lit* expression) {
    if (expression->value.empty()) result += "nil";
    else result += expression->value.toString();
}

void AstPrinter::visitUnary(const Unary* expression) {
    /*expression->right->accept(this);
    result = expression->op.lexeme + result;*/
    parenthesize(expression->op.lexeme, vector{ expression->right });
}

string AstPrinter::parenthesize(string name, vector<Expression*> expressions) {
    result += "(" + name;
    auto cur = expressions.begin();
    auto end = expressions.end();
    while (cur != end) {
        result += " ";
        (*cur)->accept(this);
        cur++;
    }
    result += ")";
    return result;
}

string AstPrinter::getResult() { return result; }