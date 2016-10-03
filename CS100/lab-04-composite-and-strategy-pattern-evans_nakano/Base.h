#include <iostream>

#ifndef BASE_H
#define BASE_H


class Base { // REQUIRED BASE CLASS
    public:
        /* Constructors */
        Base() { };

        /* Pure Virtual Functions */
        virtual double evaluate() = 0;
};

/*
You will have one type of leaf node which will represent a 
number (class Op), and two types of composite nodes. There
will be four types of nodes that have two children, capable 
of expressing the operations multiply (class Mult), divide
(class Div), add (class Add), and subtract (class Sub). There
also be one type of node that only has one child, which 
expresses squaring a value (class Sqr). Notice that any 
parentheses that would be in the expression can be
implemented in the trees structure rather than explicitly with a node.
*/

class Op: public Base {
    private:
    double data;
    
    public:
        Op(double input){
            data = input;
        }
        double evaluate(){
            return data;
        }
    
};

class Mult: public Base {
    private:
        Base *left;
        Base *right;
    public:
        Mult(Base* a, Base* b){
            left = a;
            right = b;
        }
        double evaluate(){
            return left->evaluate() * right->evaluate();
        }
        
    
};

class Div: public Base {
    private:
        Base *left;
        Base *right;
    public:
        Div(Base* a, Base* b) {
            left = a;
            right = b;
        }
        double evaluate(){
            return left->evaluate() / right->evaluate();
    }
     
};

class Add : public Base {
    private:
        Base *left;
        Base *right;
    public:
         Add(Base* a, Base* b){
            left = a;
            right = b;
        }
        double evaluate(){
            return left->evaluate() + right->evaluate();
        }
     
    
};

class Sub : public Base {
    private:
        Base *left;
        Base *right;
    public:
        Sub(Base* a, Base* b){
            left = a;
            right = b;
        }
        double evaluate(){
            return left->evaluate() - right->evaluate();
        }
 
    
};

class Sqr : public Base {
    private:
    Base *child;
    
    public:
         Sqr(Base* a){
            child = a;
            
        }
        double evaluate(){
            return child->evaluate() * child->evaluate();
        }

    
};

#endif