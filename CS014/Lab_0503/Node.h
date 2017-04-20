#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>
using namespace std;

class Node {
 friend class AVLTree;
 private:
   string data;
   Node* left;
   Node* right;
   Node* up;
   int count;
 
 public:
   void inc() { this->count++; }
   void dec() { this->count--; }
   
   
   Node(string _data);
};

#endif