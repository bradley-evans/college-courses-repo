#include "AVLTree.h"
using namespace std;


//     Node* left;
//   Node* right;
//   string data;
//   int count;

    AVLTree::AVLTree() : Node(""), root(0){}
    
    Node* AVLTree::findUnbalancedNode(Node* temp){
        if (abs(balanceFactor(temp)) == 2) {
            return temp;
        } else if (temp->up == 0) {
            return 0;
        } else {
            return findUnbalancedNode(temp->up);
        }
    }
    
    void AVLTree::rotate(Node* temp){
        // four cases.
        // find balance factors
        int balfact_left = 0, balfact_right = 0, balfact_self = 0;
        if (temp->left != 0) { balfact_left = balanceFactor(temp->left); }
        if (temp->right != 0) { balfact_right = balanceFactor(temp->right); }
        balfact_self = balanceFactor(temp);
        cout << "In rotate, for node " << temp->data << " balfact_left=" << balfact_left << " balfact_right=" << balfact_right << " balfact_self=" << balfact_self << endl;
        // case 1: left-left (2,1) case
        if (balfact_left == 1 && balfact_self == 2) {
            rotateRight(temp);
       
        // case 2: right-right (-2,-1) case
        } else if (balfact_right == -1 && balfact_self == -2) {
            rotateLeft(temp);
        
        // case 3: left-right (2,-1) case
        } else if (balfact_left == -1 && balfact_self == 2) {
            rotateLeft(temp);
            temp = temp->up;
            rotateRight(temp);
       
        // case 4: right-left (-2,1) case
        } else if (balfact_right == 1 && balfact_self == -2) {
            rotateRight(temp);
            temp = temp->up;
            rotateLeft(temp);
        
        } else {
            cout << "No valid rotate condition detected!" << endl;
        }
        
        
    }
    void AVLTree::rotateLeft(Node* DNode){
        cout << "Rotating " << DNode->data << " left..." << endl;
        printBalanceFactors(root);
        cout << endl;
        Node *BNode = 0, *CNode = 0;
        BNode = DNode->right;
        CNode = BNode->left;
        
        BNode->left = DNode;
        DNode->right = CNode;
        
        DNode->up = BNode;
        
    }
    
    void AVLTree::rotateRight(Node* DNode){
        cout << "Rotating " << DNode->data << " right..." << endl;
        printBalanceFactors(root);
        cout << endl;
        Node *BNode = 0, *CNode = 0;
        BNode = DNode->left;
        CNode = BNode->right;
        
        BNode->right = DNode;
        DNode->left = CNode;
        
        DNode->up = BNode;
        printBalanceFactors(root);
        cout << endl;
    }
    
    void AVLTree::visualizeTree(ofstream & outFS, Node *n){
        if(n){
            if(n->left){
                visualizeTree(outFS,n->left);
                outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
            }
    
            if(n->right){
                visualizeTree(outFS,n->right);
                outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
            }
        }
    }

    int AVLTree::height(Node *temp) const{
        if (temp == 0){
            return 0;   
        }
        
        int a = 1 + height(temp->left);
        int b = 1 + height(temp->right);
        
        if(a > b){
            return a;
        }
        return b;
    }

    /*
    Insert an item into the binary search tree. Be sure to keep 
    the binary search tree properties. When an item is first 
    inserted into the tree the count should be set to 1. When 
    adding a duplicate string (case sensitive), rather than 
    adding another node, the count variable should just be 
    incremented.
    */
    void AVLTree::insert(const string &val){
        if (root == 0) {
            // the tree is empty, put new node at root.
            root = new Node(val);
            root->inc();
            return;
        } else {
            addnode(root,val);
        }
    }
    
void AVLTree::addnode(Node* node, string string) {
    Node *nodeToBalance;
    if (node->data < string) {
        if (node->right != 0) {
            addnode(node->right, string);
        } else {
            node->right = new Node(string);
            node->right->up = node;
            node->right->inc();
            nodeToBalance = findUnbalancedNode(node->right);
            if (nodeToBalance!=0) { 
                cout << "Unbalanced node " << nodeToBalance->data << " detected. Rotating...";
                rotate(nodeToBalance);
            }
        }
    } else if (node->data > string) {
        if (node->left != 0) {
            addnode(node->left, string);
        } else {
            node->left = new Node(string);
            node->left->up = node;
            node->left->inc();
            findUnbalancedNode(node->left);
            nodeToBalance = findUnbalancedNode(node->left);
            if (nodeToBalance!=0) {
                cout << "Unbalanced node " << nodeToBalance->data << " detected. Rotating...";
                rotate(nodeToBalance);
            }
        }
    } else {
        node->inc();
    }
}
    
    
     /*
    Return the balance factor of a given node.
    */
    int AVLTree::balanceFactor(Node* temp){
        int hleft = height(temp->left);
        int hright = height(temp->right);
        
        return hleft - hright;
    }
    
    /*
    Traverse and print the tree in inorder notation. Print the 
    string followed by its balance factor in parentheses followed 
    by a , and one space.
    */
    void AVLTree::printBalanceFactors(){
        printBalanceFactors(root);
    }
    
    void AVLTree::printBalanceFactors(Node *temp){
        if(temp == 0){
            return;
        }
        printBalanceFactors(temp->left);
        cout << temp->data << '(' << balanceFactor(temp) << ')' << ", ";
        printBalanceFactors(temp->right);
    }
    
    /*
    Generate dotty file and visualize the tree using dotty program. 
    Call this function before and after rotation.
    */
    void AVLTree::visualizeTree(const string &outputFilename){
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