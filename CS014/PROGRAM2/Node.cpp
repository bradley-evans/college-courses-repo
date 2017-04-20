#include "Node.h"

Node::Node(std::string data) {
            this->count = 0;
            this->left = 0;
            this->right = 0;
            this->data = data;
}

void Node::inc() {     // mutator, increments count
    this->count++;
}

void Node::dec() {     // mutator, decriment count
    this->count--;
}

int Node::currcount() {              // accessor, returns count
    return this->count;
}