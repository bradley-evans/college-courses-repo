#ifndef __AVLTREE_H__
#define __AVLTREE_H__


#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>


using namespace std;

class AVLTree : public Node{

private:
  Node *root;

private:
  
  Node* findUnbalancedNode(Node* );
  void rotate(Node* );
  void rotateLeft(Node* );
  void rotateRight(Node* );
  void printBalanceFactors(Node *);
  void visualizeTree(ofstream &, Node *);
  int height(Node *temp) const;
  void addnode(Node* node, string string);

public:
    
    AVLTree();
    
    /*
    Insert an item into the binary search tree. Be sure to keep 
    the binary search tree properties. When an item is first 
    inserted into the tree the count should be set to 1. When 
    adding a duplicate string (case sensitive), rather than 
    adding another node, the count variable should just be 
    incremented.
    */
    void insert(const string &);
    
    /*
    Return the balance factor of a given node.
    */
    int balanceFactor(Node*);
    
    /*
    Traverse and print the tree in inorder notation. Print the 
    string followed by its balance factor in parentheses followed 
    by a , and one space.
    */
    void printBalanceFactors();
    
    /*
    Generate dotty file and visualize the tree using dotty program. 
    Call this function before and after rotation.
    */
    void visualizeTree(const string &);
    
};

#endif