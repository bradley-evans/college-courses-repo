#include <iostream>

#include "Base.h"
#include "Decorator.h"
using namespace std;


int main() {
    
    Op* op7 = new Op(-10);
    Op* op4 = new Op(3.7);
    Op* op3 = new Op(4);
    Op* op2 = new Op(5.1);
    
    Mult* A = new Mult(op7, op4);
    

    Add* B = new Add(op3, A);
    Sub* C = new Sub(B, op2);
    cout << "(-10 * 3.7 + 4 - 5.1) = " << C->evaluate() << endl;
    
    // now wrap it in the decroator
    Decorator* decorator = new Decorator(C);
    cout 	<< "Decorator abs: " << decorator->my_abs() << endl
		<< "Decorator ciel: " << decorator->my_ciel() << endl
		<< "Decorator floor: " << decorator->my_floor() << endl;
    
}
