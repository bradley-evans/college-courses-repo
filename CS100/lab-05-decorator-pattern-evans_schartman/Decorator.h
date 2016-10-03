#ifndef DECORATOR_H
#define DECORATOR_H

#include <cmath>
#include "Base.h"

class Decorator {
    private:
        Base* expr;
    public:
        Decorator(Base* newexpr) {
            this->expr = newexpr;
        }
        double my_abs() {
            return std::abs(expr->evaluate());
        }
        int my_floor() {
            return std::floor(expr->evaluate());
        }
        int my_ciel() {
            return std::ceil(expr->evaluate());
        }
};


#endif
