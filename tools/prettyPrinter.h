#pragma once
#include "tools.h"
#include "../parser/Expression.h"

class prettyPrinter : public LitVisitor {
public:
    //void visitBinary(const Binary& expression) override;
    //void visitGrouping(const Grouping& expression) override;
    string on_visit(Lit* expression) override;
    //void visitUnary(const Unary& expression) override;

    void print(Visitable& expression) {
        expression.accept(*this);
    }

private:
  /*  string paranthesise(const string& name,
        std::initializer_list<const Expression*> expressions);*/
};

