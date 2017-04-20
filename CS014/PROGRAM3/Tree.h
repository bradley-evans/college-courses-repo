#ifndef __TREE_H
#define __TREE_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Node.h"

class Tree {
private:
  Node *root;
  void preOrder(Node *node);
  void inOrder(Node *node);
  void postOrder(Node *node);
  void search(const std::string &, Node *);
  Node* locateLeaf(Node *, std::string);
  void addnode(Node*, std::string);
  void splitRoot(std::string);
  Node* node_search(Node* node, std::string string);
  void remove(Node* node, std::string string);
  bool isLeaf(Node* node);
  void reorder(Node* node);
  
  Node* findSmallPredecessor(Node* node);
  Node* findLargePredecessor(Node* node);

public:
  Tree( );
  ~Tree( );
  void insert(const std::string &);
  void preOrder( );
  void inOrder( );
  void postOrder( );
  void remove(const std::string &);
  bool search (const std::string &);
  void visualizeTree(const std::string &outputFilename);
  void visualizeTree(std::ofstream & outFS, Node *n);

private:
  // Add additional functions/variables here
    
};

#endif
