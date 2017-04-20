#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
    friend class BSTree;
    private:
        int count;   // counts existance of duplicates
        std::string data; // the data held in this node
        Node* left;  // next node
        Node* right; // previous node
        Node* up;    // parent node
        
    public:
        
        void inc();     // mutator, increments count
        void dec();     // mutator, decriment count
        int currcount();// accessor, returns count
        Node() {        // default constructor
            this->count = 0;
            this->left = 0;
            this->right = 0;
            this->data = "empty";
        }
        Node(std::string);
       
};

#endif