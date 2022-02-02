// some of this code was taken from Nathan Simpson on SO
#pragma once
#include "../scanner/Literal.h"

// forward declarations
class Lit;
class LitVisitor;
class Visitor;
struct Expression;

// Visitable Expressions can accept a visitor.
class Visitable
{
public:
    virtual ~Visitable() { }
    virtual void accept_visitor(Visitor& visitor) = 0;
    virtual void accept(Expression& obj);
};

struct Expression {
    virtual ~Expression() = default;
    // Our Visitor class, which will wrap our concrete visitor implementation
};

class Visitor
{
public:
    Visitor(Expression* obj);

    // Base class for concrete visitors
    template<typename Derived, typename Visitable>
    class OfType : public Expression
    {
    public:
        void visit(Visitable* visitable) {
            Derived* derived = static_cast<Derived*>(this);
            derived->on_visit(visitable);
        }
    };

    template<typename Derived, typename Visitable>
    void visit(Visitable* visitable);

private:
    Expression* m_obj;
};

template<typename Derived, typename Visitable>
void Visitor::visit(Visitable* visitable) {
    // check if our visitor is able to visit this instance
    OfType<Derived, Visitable>* visitor = dynamic_cast<OfType<Derived, Visitable>*>(m_obj);
    if (visitor) {
        visitor->visit(visitable);
    }
}

class LitVisitor : public Visitor::OfType<LitVisitor, Lit>
{
public:
    virtual string on_visit(Lit* lit) = 0;
};

class Lit : public Expression, public Visitable {
public:
    Literal value;

    Lit(Literal value)
        :value{ value } {}

    //template <typename T>
    //T accept(Visitor<T>& visitor) const {
    //    return visitor.visitLit(*this);
    //}
    void accept_visitor(Visitor& visitor) {
        visitor.visit<LitVisitor>(this);
    }
};

