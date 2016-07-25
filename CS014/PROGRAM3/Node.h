#ifndef __NODE_H
#define __NODE_H

#include <string>

class Node {

  friend class Tree;

private:
  std::string small;
  std::string large;
  
  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.
  int small_count, large_count;
  Node(std::string);
  
public:
  bool isTwoNode();
  bool isThreeNode();
};

#endif
