#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <vector>
#include <list>
#include <iostream>

#include "Base.h"
// #include "strategy.h"
class Sort;
class Container {
    protected: 
        Sort* sort_function;

    public: 
        /* Constructors */
        Container() : sort_function(NULL) { }
        Container(Sort* function); 

        /* Non Virtual Functions */
        // Set the type of sorting algorithm
        void set_sort_function(Sort* sort_func); 

        /* Pure Virtual Functions */
        // insert the top pointer of the tree into the container
        virtual void add_element(Base* element) = 0;
        // iterate through the trees and output values
        virtual void print() = 0;
        // calls on the previously set sorting-algorithm. 
        // Check if sort_function is not null, throw exception if is null
        virtual void sort() = 0;

        /* Essentially the only functions needed to sort */
        // switch tree locations
        virtual void swap(int i,int j) = 0;
        // get top pointer of tree at index i
        virtual Base* at(int i) = 0;
        // return container size;
        virtual int size() = 0;
};

class ListContainer : public Container{
    private:
        std::list<Base*> li;
        int sz;
    public: 
        ListContainer ();
        void add_element(Base* elem){
            li.push_back(elem);
            sz++;
        }  
        void print(){
            std::list<Base*>::iterator it;
            for(it=li.begin(); it != li.end(); it++){
                std::cout << (*it)->evaluate() << " " ;
            }
            std::cout << std::endl;
        }
        int size(){
            return sz;
        }
        Base* at(int i) {
            int n = 0;
            std::list<Base*>::iterator it;
            for (it=li.begin(); it!=li.end(); it++) {
                if (n==i) { 
                    return (*it); 
                }
                else { 
                    n++;
                }
            }
        }
        void swap(int i, int j) {
            std::list<Base*>::iterator it_i, it_j;
            it_i = li.begin();
            it_j = li.begin();
            int n = 0;
            while (n<i) { it_i++; n++; }
            
            n = 0;
            while (n<j) { it_j++; n++; }
            std::swap(*it_i,*it_j);
            // Base* temp; 
            // temp = it_i;
            // it_i = it_j;
            // it_j = temp;
           
        }
        void set_sort_function(Sort* sort_func){
            sort_function = sort_func;
        }
        void sort();
};

class VectorContainer : public Container {
    private: 
        std::vector<Base*> v1;
        int sz;
    public:
        VectorContainer () {
            sz = 0;    
        }
        void add_element(Base* elem) {
            v1.push_back(elem);
            sz++;
        }
        void print(){
            for(int i = 0; i < v1.size(); i++){
                std::cout << v1.at(i)->evaluate() << ' ';
            }
            std::cout << std::endl;
        }
        int size(){
            return sz;
        }
        void swap(int i, int j){
            Base* temp;
            temp = v1.at(i);
            v1.at(i) = v1.at(j);
            v1.at(j) = temp;
        }
        Base* at(int i) {
            return v1.at(i);
        }
        void set_sort_function(Sort* sort_func){
            sort_function = sort_func;
        }
        void sort();
};


#endif // __CONTAINER_H__
