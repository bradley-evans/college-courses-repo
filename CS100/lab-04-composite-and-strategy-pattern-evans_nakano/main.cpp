#include <iostream>

#include "Base.h"
#include "container.h"
#include "strategy.h"
using namespace std;


int main() {
    // Testing the composite pattern
    
    
    
    
    Op* op7 = new Op(7);
    Op* op4 = new Op(4);
    Op* op3 = new Op(3);
    Op* op2 = new Op(2);
    
    Mult* A = new Mult(op7, op4);
    

    Add* B = new Add(op3, A);
    Sub* C = new Sub(B, op2);
    Sqr* D = new Sqr(C);
    cout << "(7 * 4 + 3 - 2)^2 = " << D->evaluate() << endl;
    

    // Testing the strategy pattern
    VectorContainer* container_vec = new VectorContainer();
    ListContainer* container_lis = new ListContainer();
    container_vec->add_element(A);
    container_vec->add_element(B);
    container_vec->add_element(C);
    container_vec->add_element(D);
    
    container_lis->add_element(A);
    container_lis->add_element(B);
    container_lis->add_element(C);
    container_lis->add_element(D);
    cout << "list before (1,3) swap: " << endl;
    container_lis->print();
    container_lis->swap(1,3);
    cout << "list after (1,3) swap: " << endl;
    container_lis->print();

    cout << "Container (vector) Before Sort: " << endl;
    container_vec->print();
    cout << endl;
    cout << "Container (list) Before Sort: " << endl;
    container_lis->print();
    cout << endl;
    
    cout << "Container (vec) After Sort (selectionsort): " << endl;
    container_vec->set_sort_function(new BubbleSort());
    container_vec->sort();
    container_vec->print();
    
    cout << "Container (list) After Sort (bubblesort): " << endl;
    container_lis->set_sort_function(new BubbleSort());
    container_lis->sort();
    container_lis->print();
    
    
    
}