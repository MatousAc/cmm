#pragma once
#include "../scanner/Token.h"

struct Lit;

struct Expression {
    virtual ~Expression() = default;

    template <typename T>    
    class Visitor {
    public:
        virtual T visitLit(const Lit& expression) = 0;
    };
    template <typename T>
    T accept(Visitor<T>& visitor) const {return T();};
};

struct Lit : public Expression {
    Literal value;

    Lit(Literal value)
        :value{ value } {}

    template <typename T>
    T accept(Visitor<T>& visitor) const {
        return visitor.visitLit(*this);
    }
};
