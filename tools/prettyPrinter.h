#pragma once
#include <string.h>
#include "tools.h"
#include "../parser/Expression.hpp"
using std::string;

class prettyPrinter : Expression::Visitor<string> {
public:
    //void visitBinary(const Binary& expression) override;
    //void visitGrouping(const Grouping& expression) override;
    string visitLit(const Lit& expression) override;
    //void visitUnary(const Unary& expression) override;

    string print(const Expression& expression) {
        return expression.accept(*this);
    }

private:
  /*  string paranthesise(const string& name,
        std::initializer_list<const Expression*> expressions);*/
};
