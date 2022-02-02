#pragma once
#include "../include.h"
#include "../parser/Expression.hpp"

class PrettyPrinter : Visitor {
    string result;
public:
    PrettyPrinter() : result{} {};
    void read(const Expression* expression);
    //void visitBinary(const Binary& expression) override;
    //void visitGrouping(const Grouping& expression) override;
    void visitLit(const Lit* expression);
    //void visitUnary(const Unary& expression) override;

  /*  string paranthesise(const string& name,
        std::initializer_list<const Expression*> expressions);*/
    string getResult();
};
