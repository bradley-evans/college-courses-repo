#ifndef BSTREE_H
#define BSTREE_H


#include "Node.h"
#include <iostream>
#include <string>


class BSTree {
    private:
        Node *root;
        
        // recursive private helper functions
        std::string largest_recursive(Node *node) const;
        std::string smallest_recursive(Node *node) const;
        void addnode(Node *node, std::string string);
        void inOrder_recursive(Node *node);
        void postOrder_recursive(Node *node);
        void preOrder_recursive(Node *node);
        void remove_node(Node *node);
        void remove_search(Node *node, const std::string &string);
        Node* minNode(Node *node);
        Node* maxNode(Node *node);
        int height (Node *node, int i) const;
        bool search(const std::string &searchstr, Node* node) const;
        Node* nodesearch(const std::string &searchstr, Node* node) const;
    
    public:
        BSTree() { root = 0; }
        void insert(const std::string &newdata);
        /* 
        Insert an item into the binary search tree. Be sure to keep the binary 
        search tree properties. When an item is first inserted into the tree the
        count should be set to 1. When adding a duplicate string (case 
        sensitive), rather than adding another node, the count variable should 
        just be incremented.
        */
        bool search(const std::string &searchstr) const;
        /*
        Search for a string in the binary search tree. It should return true if
        the string is in the tree, and false otherwise.
        */
        std::string largest() const;
        /*
        Find and return the largest value in the tree. Return an empty string if
        the tree is empty.
        */
        std::string smallest() const;
        /*
        Find and return the smallest value in the tree. Return an empty string
        if the tree is empty.
        */
        int height (const std::string &searchstr) const;
        /*
        Compute and return the height of a particular string in the tree. The 
        height of a leaf node is 0 (count the number of edges on the longest 
        path). Return -1 if the string does not exist.
        */
        void remove(const std::string &searchstr);
        /*
        Remove a specified string from the tree. Be sure to maintain all binary
        search tree properties. If removing a node with a count greater than 1,
        just decrement the count, otherwise, if the count is simply 1, remove 
        the node. You MUST follow the remove algorithm shown in the slides and 
        discussed in class or else your program will not pass the test 
        functions. When removing, if removing a leaf node, simply remove the 
        leaf. Otherwise, if the node to remove has a left child, replace the 
        node to remove with the largest string value that is smaller than the 
        current string to remove (i.e. find the largest value in the left 
        subtree of the node to remove). If the node has no left child, replace 
        the node to remove with the smallest value larger than the current 
        string to remove (i.e. find the smallest value in the right subtree of 
        the node to remove).
        */
        void inOrder();
        void postOrder();
        void preOrder();
};


#endif