#include "Expression.h"
Visitor::Visitor(Expression* obj) : m_obj(obj) {}


void Visitable::accept(Expression& visitor) {
    Visitor wrapped(&visitor);
    accept_visitor(wrapped);
}
