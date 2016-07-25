#include "BSTree.h"
using namespace std;



void BSTree::insert(const string &newdata) {
/* 
Insert an item into the binary search tree. Be sure to keep the binary 
search tree properties. When an item is first inserted into the tree the
count should be set to 1. When adding a duplicate string (case 
sensitive), rather than adding another node, the count variable should 
just be incremented.
*/
    if (root == 0) {
        // the tree is empty, put new node at root.
        root = new Node(newdata);
        root->inc();
        return;
    } else {
        addnode(root,newdata);
    }
}

bool BSTree::search(const string &searchstr) const {
/*
Search for a string in the binary search tree. It should return true if
the string is in the tree, and false otherwise.
*/
    if (root == 0) {
        // the tree is empty, you doofus
        return false;
    }
    return search(searchstr,root);
}
bool BSTree::search(const string &searchstr, Node* node) const {
    //cout << "Searching recursively (at " << node->data << ")...";
    if (node->data == searchstr) {
        //cout << "Found " << node->data << "." << endl;
        return true;
    }
    if (searchstr > node->data) {
        if (node->right == 0) {
            //cout << "No right child of " << node->data << "." << endl;
            return false;
        }
        return search(searchstr, node->right);
    } else {
        if (node->left == 0) {
            //cout << "No left child of " << node->data << "." << endl;
            return false;
        }
        return search(searchstr,node->left);
    }
}
Node* BSTree::nodesearch(const string &searchstr, Node* node) const {
    if (node->data == searchstr) {
        return node;
    }
    if (searchstr > node->data) {
        if (node->right == 0) {
            return 0;
        }
        return nodesearch(searchstr, node->right);
    } else {
        if (node->left == 0) {
            return 0;
        }
        return nodesearch(searchstr,node->left);
    }
}

string BSTree::largest() const {
    return largest_recursive(root);
}
string BSTree::largest_recursive(Node* node) const {
/* 
Find and return the largest value in the tree. Return an empty string if
the tree is empty.
*/
    if (root == 0) {
        return "";
    }
    if (node->right == 0) {
        return node->data;
    }
    return largest_recursive(node->right);
}
string BSTree::smallest() const {
    return smallest_recursive(root);
}
string BSTree::smallest_recursive(Node* node) const {
/*
Find and return the smallest value in the tree. Return an empty string
if the tree is empty.
*/
    if (root == 0) {
        return "";
    }
    if (node->left == 0) {
        return node->data;
    }
    return smallest_recursive(node->left);

}
int BSTree::height (const string &searchstr) const {
/*
Compute and return the height of a particular string in the tree. The 
height of a leaf node is 0 (count the number of edges on the longest 
path). Return -1 if the string does not exist.
*/
    if (!search(searchstr)) {
        //cout << "String " << searchstr << " not found." << endl;
        return -1;
    }
    Node *node = nodesearch(searchstr, root);
    return height(node,0);
}
int BSTree::height(Node *node, int i) const {
    int leftheight = 0, rightheight = 0;
    if (node->left != 0) {
        leftheight = height(node->left,1);
    }
    if (node->right != 0) {
        rightheight = height(node->right,1);
    }
    if (leftheight > rightheight) {
        i = i+leftheight;
    } else {
        i = i+rightheight;
    }
    return i;
}
void BSTree::remove(const string &searchstr) {
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
    if (root == 0) {
        // the tree is empty, nothing to see here.
        // otherwise, move on to the recursive private helper function
        return;
    } else {
        remove_search(root,searchstr);
    }
}
void BSTree::remove_search(Node* node, const string &string) {
    
    
    if (node->data == string) {
        // we found the node for deletion
        //cout << "REMOVE OPERATION: DELETING [" << node->data << "]...";
        if (node->count > 1) {
            //cout << "Node has a count greater than 1. Decrementing count." << endl;
            node->dec();
        } else {
            remove_node(node);
        }
    } else if (node->data < string) {
        if (node->right == 0) {
            // dead end found
            return;
        } else {
            remove_search(node->right, string);
        }
    } else if (node->data > string) {
        if (node->left == 0) {
            //cout << "Node not found." << endl;
            // dead end found
            return;
        } else {
            remove_search(node->left, string);
        }
    }
}
void BSTree::remove_node(Node* node) { // actually delete a node
    // there are five cases. case 0 is an empty tree, which is handled above.
    //Node *swapNode;
    
    //case 1: a leaf, simply delete it
    if (node->left == 0 && node->right == 0) {
        //cout << "Leaf...";
        if (node->up == 0) {
            // this is a root node and a leaf
            //cout << "Singular root node detected...";
            root = 0;
            delete node;
            //cout << "Deleted node." << endl;
            return;
        }
        if (node->data > node->up->data) {
            //cout << "Right Child...";
            // then this is the right child and a leaf
            if (node->up == 0) {
                root = 0;
            } else {
                node->up->right = 0;
            }
            delete node;
            //cout << "Deleted node." << endl;
        } else {
            // then it must be the left child
            //cout << "Left Child...";
            if (node->up == 0) {
                root = 0;
            } else {
                node->up->left = 0;
            }
            delete node;
            //cout << "Deleted node." << endl;
        }
    
    // case 2: a node with one left child
    } else if (node->left != 0 && node->right == 0) {
        //cout << "Node with one left child...";
        Node *swapNode = maxNode(node->left);
        string tempdata = swapNode->data;
        int tempcount = swapNode->count;
        remove_node(swapNode);
        node->data = tempdata;
        node->count = tempcount;
        /*
        else if (node->data > node->up->data) {
            // then node is the right child of parent
            //cout << "Right child of parent...";
            node->up->right = node->left;
            delete node;
            //cout << "Deleted node." << endl;
        } else {
            // then it must be the left child of parent
            //cout << "Left child of parent...";
            node->up->left = node->left;
            delete node;    
            //cout << "Deleted node." << endl;
        }
        */
    // case 3: a node with one right child
    } else if (node->left == 0 && node->right != 0) {
        //cout << "Node with one right child...";  
        Node *swapNode = minNode(node->right);
        string tempdata = swapNode->data;
        int tempcount = swapNode->count;
        remove_node(swapNode);
        node->data = tempdata;
        node->count = tempcount;
        /*
        else if (node->data < node->up->data) {
            //cout << "Left child of parent...";
            // then node is the right child of parent
            node->up->left = node->right;
            delete node;
            //cout << "Deleted node." << endl;
        } else {
            //cout << "Right child of parent...";
            // then it must be the left child of parent
            node->up->right = node->right;
            delete node;       
            //cout << "Deleted node." << endl;
        }
        */
    // case 4: a node with two children
    } else if (node->left != 0 && node->right != 0) {
        //cout << "Node with two children...";
        // find inorder successor node
        Node *swapNode = maxNode(node->left);
        // store all data from this node
        string tempdata = swapNode->data;
        int tempcount = swapNode->count;
        //cout << "This node's data will be changed to [" << tempdata << "]. Calling remove recursively on " << swapNode->data << endl;
        remove_node(swapNode);
        node->data = tempdata;
        node->count = tempcount;
        //cout << "Two-child node deletion complete." << endl;;
    }
}
Node* BSTree::minNode(Node* node) {
    if (node->left == 0) {
        return node;
    }
    return minNode(node->left);
}
Node* BSTree::maxNode(Node* node) {
    if (node->right == 0) {
        return node;
    }
    return maxNode(node->right);
}

void BSTree::addnode(Node* node, string string) {
    if (node->data < string) {
        if (node->right != 0) {
            addnode(node->right, string);
        } else {
            node->right = new Node(string);
            node->right->up = node;
            node->right->inc();
        }
    } else if (node->data > string) {
        if (node->left != 0) {
            addnode(node->left, string);
        } else {
            node->left = new Node(string);
            node->left->up = node;
            node->left->inc();
        }
    } else {
        node->inc();
    }
}


void BSTree::preOrder() {
    preOrder_recursive(root);
}
void BSTree::preOrder_recursive( Node* curr ) {

    if (curr == 0 || root == 0) {
          return;
    }
    cout << curr->data << "(" << curr->currcount() << "), ";
    preOrder_recursive(curr->left);  
    preOrder_recursive(curr->right);

}

void BSTree::inOrder() {
    inOrder_recursive(root);
}
void BSTree::inOrder_recursive( Node* curr ) {
    if ( curr == 0 || root == 0 ) {
        return;
    }
    inOrder_recursive(curr->left);
    cout << curr->data << "(" << curr->currcount() << "), ";
    inOrder_recursive(curr->right);
}

void BSTree::postOrder() {
    postOrder_recursive(root);
}
void BSTree::postOrder_recursive( Node* curr ) {

    if (curr == 0 || root == 0) {
          return;
    }
    postOrder_recursive(curr->left);  
    postOrder_recursive(curr->right);
    cout << curr->data << "(" << curr->currcount() << "), ";

}

