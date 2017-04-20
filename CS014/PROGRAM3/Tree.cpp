
#include <string>
#include "Tree.h"

using namespace std;



// PRIVATE FUNCTIONS


void Tree::preOrder(Node *node) {
    
    if (node == 0) {
        return;
    }
    if (node->large.empty()) {
        // this is a two-node
        cout << node->small << ", ";
        preOrder(node->left);
        preOrder(node->right);
    } else {
        cout << node->small << ", ";
        preOrder(node->left);
        cout << node->large << ", ";
        preOrder(node->middle);
        preOrder(node->right);
    }
    return;
}
void Tree::inOrder(Node *node) {
    
    if (node == 0) {
        return;
    }
    if (node->isTwoNode()) {
        // then this is a two node
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->right);
    } else {
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->middle);
        cout << node->large << ", ";
        inOrder(node->right);
    }
    return;
}
void Tree::postOrder(Node *node) {
    
    if (node == 0) {
        return;
    }
    if (node->large.empty()) {
        // two node
        postOrder(node->left);
        postOrder(node->right);
        cout << node->small << ", ";
    } else {
        postOrder(node->left);
        postOrder(node->middle);
        cout << node->small << ", ";
        postOrder(node->right);
        cout << node->large << ", ";
    }
}
void Tree::search(const string &, Node *) {

}
Node* Tree::locateLeaf(Node *node, string string) {
    // cout /**/ << "Finding leaf node...";
    if (root == 0) {
        // cout /**/ << "This is the root node!...";
        // this will be inserted into a root node
        return root;
    }
    if ((string == node->small) || (string == node->large)) {
        // cout /**/ << "Match found...";
        // then we have a data match
        return node;
    }
    if (node->left == 0 && node->right == 0) {
        // cout /**/ << "Leaf with SMALL[" << node->small << "] LARGE [" << node->large << "] found...";
        // we found a leaf! Wonderful.
        return node;
    }
    if (node->left != 0 || node->right != 0) {
        // then this node isn't a leaf, and things get complicated
        if (!node->small.empty() && node->large.empty()) {
            // cout /**/ << "Two node with children...";
            // then we are in a two-node with children
            if (string < node->small && node->left != 0) {
                // cout /**/ << "Checking left child...";
                // the string is smaller than the two node's value and a left child exists
                return locateLeaf(node->left, string);
            }
            if (string > node->small && node->right != 0) {
                // cout /**/ << "Checking right child...";
                // the string is larger than the two-node's value and a right child exists
                return locateLeaf(node->right, string);
            }
            // cout /**/ << "Something went wrong! two-node findNode";
            return 0;
        }
        if (!node->small.empty() && !node->large.empty()) {
            // cout /**/ << "Three node with children...";
            // then we are in a three node with children
            if (string < node->small && node->left != 0) {
                // cout /**/ << "Checking left child...";
                // the string is smaller than the three node's small value and a left child exists
                return locateLeaf(node->left, string);
            }
            if (string > node->large && node->right != 0) {
                // cout /**/ << "Checking right child...";
                // the string is larger than the two-node's large value and a right child exists
                return locateLeaf(node->right, string);
            }
            if (string > node->small && string < node->large && node->middle != 0) {
                // cout /**/ << "Checking middle child...";
                // the string is in between the three node's values and a middle child exists
                return locateLeaf(node->middle, string);
            }
            // cout /**/ << "Something went wrong! three-node findNode";
            return 0;
        }
    }
    return 0;
}
void Tree::addnode(Node *target, string str) {
    string temp;
    // simplest cases
    if (root == 0) {
        // cout /**/ << "Inserting at root node." << endl;
        // then this is a root node
        root = new Node(str);
        return;
    }
    if (target->small == str) {
        // cout /**/ << "Incrementing." << endl;
        // data match
        target->small_count++;
        return;
    }
    if (target->large == str) {
        // cout /**/ << "Incrementing." << endl;
        // data match
        target->large_count++;
        return;
    }
    // more complex cases
    if (!target->small.empty() && target->large.empty()) {
        // cout /**/ << "Inserting into a two-node...";
        // case: a two node
        if (str > target->small) {
            // cout /**/ << "Inserting case: new str larger than existing str in node...";
            // case: a two-node where the new str is larger than the existing data
            target->large = str;
            // cout /**/ << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
            return;
        } 
        if (str < target->small) {
            // cout /**/ << "Inserting case: new str smaller than existing str in node...";
            // case: a two node where the new str is smaller than the existing data
            target->large = target->small;
            target->small = str;
            // cout /**/ << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
            return;
        }
    }
    if (target->isThreeNode()) {
        // case: a three node
        if (target->parent == 0) {
             // cout /**/ << "A root three-node was detected, splitting root...";
             splitRoot(str);
             return;
        } else if (target->parent->isTwoNode()) {
            // cout /**/ << "Inserting into a three node with two node parent...";
                // case: parent is a two node
                if (target->parent->left == target) {
                    if (str < target->small) {
                        // promote the small node and split
                        // cout /**/ << "Inserting and promoting " << target->small << "...";
                        addnode(target->parent, target->small);
                        target->small = str;
                        // cout /**/ << "Placed " << str << " into small value of node...";
                        if (target->parent->middle == 0) {
                            // cout /**/ << "Creating a middle node...";
                            target->parent->middle = new Node(target->large);
                            Node* newmiddle = target->parent->middle;
                            newmiddle->parent = target->parent;
                            // cout /**/ << "New middle node is [" << newmiddle->small << "] [" << newmiddle->large << "] ...";
                        } else if (target->parent->middle != 0) {
                            addnode(target->parent->middle, target->large);
                        }
                        target->large.clear();
                        // cout /**/ << "Target node is now [" << target->small << "] [" << target->large << "]" << endl;
                        return;
                    }
                    if (str > target->large) {
                        // promote the large node and split
                        // cout /**/ << "Inserting and promoting " << target->large << "...";
                        addnode(target->parent, target->large);
                        if (target->parent->middle == 0) {
                            // cout /**/ << "Creating a middle node...";
                            target->parent->middle = new Node(str);
                            target->parent->middle->parent = target->parent;
                        } else if (target->parent->middle != 0) {
                            addnode(target->parent->middle, target->small);
                        }
                        target->large.clear();
                        // cout /**/ << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                        return;
                    }
                    if (str > target->small && str < target->large) {
                        // promote the new node and split
                        // cout /**/ << "Promoting " << str << "...";
                        addnode(target->parent, str);
                        if (target->parent->middle == 0) {
                            // cout /**/ << "Creating a middle node...";
                            target->parent->middle = new Node(target->large);
                            target->parent->middle->parent = target->parent;
                        } else if (target->parent->middle != 0) {
                            addnode(target->parent->middle, target->large);
                        }
                        target->large.clear();
                        // cout /**/ << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                        return;
                    }
                } else if (target->parent->right == target) {
                    if (str < target->small) {
                        // promote the small node and split
                        // cout /**/ << "Inserting and promoting " << target->small << "...";
                        addnode(target->parent, target->small);
                        target->small = str;
                        // cout /**/ << "Placed " << str << " into small value of node...";
                        if (target->parent->middle == 0) {
                            // cout /**/ << "Creating a middle node...";
                            target->parent->middle = new Node(target->small);
                            Node* newmiddle = target->parent->middle;
                            newmiddle->parent = target->parent;
                            // cout /**/ << "New middle node is [" << newmiddle->small << "] [" << newmiddle->large << "] ...";
                        } else if (target->parent->middle != 0) {
                            addnode(target->parent->middle, target->large);
                        }
                        target->small = target->large;
                        target->large.clear();
                        // cout /**/ << "Target node is now [" << target->small << "] [" << target->large << "]" << endl;
                        return;
                    }
                    if (str > target->large) {
                        // promote the large node and split
                        // cout /**/ << "Inserting and promoting " << target->large << "...";
                        addnode(target->parent, target->large);
                        if (target->parent->middle == 0) {
                            // cout /**/ << "Creating a middle node...";
                            target->parent->middle = new Node(target->small);
                            target->parent->middle->parent = target->parent;
                        } else if (target->parent->middle != 0) {
                            addnode(target->parent->middle, target->small);
                        }
                        target->small = str;
                        target->large.clear();
                        // cout /**/ << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                        return;
                    }
                    if (str > target->small && str < target->large) {
                        // promote the new node and split
                        // cout /**/ << "Promoting " << str << "...";
                        addnode(target->parent, str);
                        if (target->parent->middle == 0) {
                            // cout /**/ << "Creating a middle node...";
                            target->parent->middle = new Node(target->large);
                            target->parent->middle->parent = target->parent;
                        } else if (target->parent->middle != 0) {
                            addnode(target->parent->middle, target->large);
                        }
                        target->large.clear();
                        // cout /**/ << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                        return;
                    }
                }   
        }
        if (target->parent->isThreeNode()) {
            if (target->parent->left == target) {
                // Target is a left-child three node with a three node parent
                if (str < target->small) {
                    temp = target->small;
                    target->small = str;
                    addnode(target->parent,temp);
                    return;
                } else if (str > target->large) {
                    temp = target->large;
                    target->large = str;
                    addnode(target->parent,temp);
                    return;
                } else {
                    addnode(target->parent,str);
                    return;
                }
                
            } else if (target->parent->right == target) {
                
                // Target is a right-child three node with a three node parent
                if (str < target->small) {
                    
                } else if (str > target->large) {
                    
                } else {
                    
                }
                
            } else {
                // Target is a middle-child three node with a three node parent
                if (str < target->small) {
                    temp = target->small;
                    target->small = str;
                    addnode(target->parent,temp);
                    return;
                } else if (str > target->large) {
                    
                } else {
                    
                }
                
            }
        
        
        
        }
    }
}
void Tree::splitRoot(string string) {
    if (string < root->small) {
        // promote small to root
        // cout /**/ << "splitting root case: string less than root small...";
        root->parent = new Node(root->small);
        root->parent->left = root;
        root->parent->right = new Node(root->large);
        root->parent->right->parent = root->parent;
        root->small = string;
        root->large.clear();
        root = root->parent;
        // cout /**/ << "Root successfully split." << endl;
        return;
    }
    if (string > root->large) {
        // promote large to root
        // cout /**/ << "splitting root case: string greater than root large...";
        root->parent = new Node(root->large);
        root->parent->right = root;
        root->parent->left = new Node(root->small);
        root->parent->left->parent = root->parent;
        root->small = string;
        root->large.clear();
        root = root->parent;
        // cout /**/ << "Root successfully split with " << root->small << " as root." << endl;
        return;
    }
    if (string > root->small && string < root->large) {
        // promote new string to root
        // cout /**/ << "splitting root case: new string is middle value...";        
        root->parent = new Node(string);
        root->parent->left = root;
        root->parent->right = new Node(root->large);
        root->parent->right->parent = root->parent;
        root->large.clear();
        if (!isLeaf(root)) {
            // Node *newLeft, *newRight, *middle;
            // newLeft = root->parent->left;
            // newRight = root->parent->right;
            Node *middle = root->middle;
            root->middle = 0;
            //cout << "middle large: " << middle->large << endl;
            //cout << "root right: " << root->right->small;
            root->parent->right->right = root->right;
            root->parent->right->right->parent = root->parent->right;
            root->right = 0;
            root->parent->left->right = new Node(middle->small);
            root->parent->right->left = new Node(middle->large);
            delete middle;
            //cout << "root->parent->right->small: " << root->parent->right->small << endl;
            //newLeft->right = new Node(middle->small);
            //newRight->left = new Node(middle->large);
        }
        root = root->parent;
        // newRight->left = new Node(middle->large);
        
        // root->large.clear();
        // root = root->parent;
        // cout /**/ << "Root successfully split with " << root->small << " as root." << endl;
        return;
    }
}
Node* Tree::node_search(Node* node, string string) {
    if (node == 0) {
        return 0;
    }
    if (node->small == string || node->large == string ) {
        return node;
    }
    if (node->isTwoNode()) {
        if (string < node->small) {
            return node_search(node->left,string);
        } else if (string > node->small) {
            return node_search(node->right,string);
        }
    }
    if (node->isThreeNode()) {
        if (string < node->small) {
            return node_search(node->left,string); 
        } else if (string > node->large) {
            return node_search(node->right,string);
        } else {
            return node_search(node->middle,string);
        }
    }
    return 0;
}
void Tree::remove(Node* node, string string) {
    if (node == 0) {
        // then the earlier node_search call returned that the node was not
        // found. Return.
        return;
    }
    if (node->small == string && node->small_count > 1) {
        node->small_count--;
        // cout /**/ << "Node with count > 1 detected, decrementing...";
        return;
    } else if (node->large == string && node->large_count > 1) {
        node->large_count--;
        // cout /**/ << "Node with count > 1 detected, decrementing...";
        return;
    }
    if (node == root) {
        // These cases cover what occurs when the root node must be deleted.
        // cout /**/ << "At root node...";
        if (isLeaf(node)) {
            // cout /**/ << "Root is a leaf node...";
            // The root node is a leaf node (it is the only node).
            if (node->isTwoNode()) {
                // The root node is a solitary two-node. Just delete it.
                root = 0;
                // cout /**/ << "Deleting two-node root leaf...";
                delete node;
                return;
            } else {
                // Then the root node is a three node and also the only node.
                // Replace the small value with the large one, call it a day.
                // Or, alternatively, just delete the large value if that is
                // the target.
                // cout /**/ << "Deleting value in three-node root leaf...";
                if (string == node->large) {
                    node->large.clear();
                    return;
                } else {
                    node->small = node->large;
                    node->large.clear();
                    return;
                }
            }
        } else {
            // for now, carrying on with other cases.
            // cout /**/ << "Root is not a leaf, carrying on to other cases...";
            
        }
    }
    // If this is an internal node, swap the node with the inorder successor
    // Removal and rebalancing will always begin at a leaf node.
    
    if (!isLeaf(node)) {
        // cout /**/ << "Removing an internal node...";
        Node* predecessor = 0;
        if (node->small == string) {
            // cout /**/ << "The inorder predecessor for " << string << " is ";
            predecessor = findSmallPredecessor(node->left);
            if (predecessor->isTwoNode()) {
                node->small = predecessor->small;
                // cout /**/ << predecessor->small << "...";
            } else {
                node->small = predecessor->large;
                // cout /**/ << predecessor->large << "...";
            }
            // cout /**/ << "Removing predecessor " << node->small << "...";
            remove(predecessor, node->small);
            return;
        } else {
            predecessor = findLargePredecessor(node->middle);
            if (predecessor->isTwoNode()) {
                node->small = predecessor->small;
                // cout /**/ << predecessor->small << "..." << endl;
            } else {
                node->small = predecessor->large;
                // cout /**/ << predecessor->large << "..." << endl;
            }
            // cout /**/ << "Removing predecessor " << node->large << "...";
            remove(predecessor, node->large);
            return;
        }
    }
    if (isLeaf(node)) {
        // cout /**/ << "Removing a leaf node...";
        if (node->isThreeNode()) {
            // cout /**/ << "Removing a value in a three-node leaf...";
            if (node->small == string) {
                node->small = node-> large;
                node->large.clear();
                return;
            } else {
                node->large.clear();
                return;
            }
        } else {
            // now it gets complicated
            // cout /**/ << "Removing a two-node and reordering the tree...";
            if (node->parent->left == node) {
                node->parent->left = 0;
                // segfault for test 10 occurs here
                reorder(node->parent);
                return;
            } else if (node->parent->middle == node) {
                node->parent->middle = 0;
                reorder(node->parent);
                delete node;
                return;
            } else if (node->parent->right == node) {
                node->parent->right = 0;
                reorder(node->parent);
                delete node;
                return;
            }
            return;
        }
    }
}

void Tree::reorder(Node* node) {
    
    // ROOT NODE CASES
    if (node == root) {
        // then we are performing fixes on a root node
        if (node->isTwoNode()) {
            if (node->left == 0) {
                if (node->right->isTwoNode()) {
                    node->right->large = node->right->small;
                    node->right->small = node->small;
                    root = node->right;
                    root->parent = 0;
                    delete node;
                    return;
                } else {
                    node->left = new Node(node->small);
                    node->small = node->right->small;
                    node->right->small = node->right->large;
                    return;
                }
            } else if (node->right == 0) {
                if (node->left->isTwoNode()) {
                    node->left->large = node->small;
                    root = node->left;
                    root->parent = 0;
                    delete node;
                    return;
                } else {
                    node->right = new Node(node->small);
                    node->left->large = node->small;
                    node->left->large.clear();
                    return;
                }
            }
        } else if (node->isThreeNode()) {
            if (node->left == 0) {
                if (node->middle->isTwoNode()) {
                    node->left = node->middle;
                    node->middle = 0;
                    node->left->large = node->left->small;
                    node->left->small = node->small;
                    node->small = node->large;
                    node->large.clear();
                    return;
                }
                
            } else if (node->middle == 0) {
                if (node->left->isTwoNode()) {
                    node->left->large = node->small;
                    node->small = node->large;
                    node->large.clear();
                    return;
                }
            
            } else if (node->right == 0) {
                if (node->middle->isTwoNode()) {
                    node->right = node->middle;
                    node->middle = 0;
                    node->right->large = node->large;
                    node->large.clear();
                    return;
                }
            }
        }
    }
    
    // INTERNAL NODE CASES
    cout << "Warning! No reorder case was hit...";
}

bool Tree::isLeaf(Node* node) {
    if (node->left == 0 && node->right == 0 && node->middle == 0) {
        return true;
    } else {
        return false;
    }
}
Node* Tree::findSmallPredecessor(Node* node) {
    if (node->left != 0) {
        return findSmallPredecessor(node->left); 
    } else {
        return node;
    }
}
Node* Tree::findLargePredecessor(Node* node) {
    if (node->right != 0) {
        return findLargePredecessor(node->right); 
    } else {
        return node;
    }
}


// PUBLIC FUNCTIONS
Tree::Tree() {
    root = 0;
}
Tree::~Tree() {

}

void Tree::insert(const string &string) {
    Node *target = 0;
    // cout /**/ << "Inserting [" << string << "]...";
    target = locateLeaf(root, string);
    addnode(target,string);
}
void Tree::preOrder( ) {
    preOrder(root);
}
void Tree::inOrder( ) {
    inOrder(root);
}
void Tree::postOrder( ) {
    postOrder(root);
}
void Tree::remove(const string &string) {
    // cout /**/ << endl << "Beginning remove operation for [" << string << "] ...";
    Node *target = node_search(root,string);
    remove(target,string);
    // cout /**/ << "Remove complete." << endl;
}
bool Tree::search(const string &string) {
    Node *node = node_search(root,string);
    //cout << "NODE SEARCH VALUE: " << node << endl;
    if (node != 0) {
        return true;
    } else {
        return false;
    }
}

/*
=============================
VISUALIZATION FUNCTIONS
=============================
*/

void Tree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
//---------------------------------------------------
void Tree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        string parentData = "\"" + n->small;
        if(n->large != ""){
            parentData += ", " + n->large + "\"";
        }
        else{
            parentData += "\"";
        }
        outFS<<parentData << "[ label = "<<parentData<<"];"<<endl;
        
        if(n->left){
            string childData = "\"" + n->left->small;
            if(n->left->large!=""){
                childData += ", " + n->left->large + "\"";
            }
            else{
                childData += "\"";
            }
            visualizeTree(outFS,n->left);
            outFS<<parentData<<" ->  "<<childData<<";"<<endl;
        }
        
        if(n->middle){
            string childData =  "\""+n->middle->small;
            if(n->middle->large!=""){
                childData += ", " + n->middle->large + "\"";
            }
            else{
                childData += "\"";
            }
            visualizeTree(outFS,n->middle);
            outFS<<parentData<<" ->  "<<childData<<";"<<endl;
        }
        
        if(n->right){
            string childData =  "\"" + n->right->small;
            if(n->right->large != ""){
                childData += ", " + n->right->large + "\"";
            }
            else{
                childData += "\"";
            }
            visualizeTree(outFS,n->right);
            outFS<<parentData<<" ->  "<<childData<<";"<<endl;
        }
    }
}