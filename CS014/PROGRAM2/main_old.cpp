#include <iostream>
#include <string>
#include "BSTree.h"
using namespace std;

int main() {
    
    BSTree tree;
    string currstring;
    int i;
    
    for (i=0;i<20;i++) {
        cin >> currstring;
        tree.insert(currstring);
        cout << "Added " << currstring << " to tree." << endl;
    }
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Pre Order: ";
    tree.preOrder();
    cout << endl;
    cout << "Post Order: ";
    tree.postOrder();
    cout << endl;
    cout << "Largest item in tree: ";
    cout << tree.largest() << endl;
    cout << "Smallest item in tree: ";
    cout << tree.smallest() << endl;
    cout << "Checking to see if 'lima' is still in the list..." << endl;
    tree.search("lima");
    cout << "Height of lima: " << tree.height("lima") << endl;
    cout << "Height of golf: " << tree.height("golf") << endl;
    cout << "Height of oscar: " << tree.height("oscar") << endl;
    cout << "Height of fakestring: " << tree.height("fakestring") << endl;
    cout << "Deleting 'quebec' ..." << endl;
    tree.remove("quebec");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'charlie' ..." << endl;
    tree.remove("charlie");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'juliet' ..." << endl;
    tree.remove("juliet");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'epsilon' ..." << endl;
    tree.remove("epsilon");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'golf' ..." << endl;
    tree.remove("golf");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Checking to see if 'lima' is still in the list..." << endl;
    if (tree.search("lima")) { cout << "Found lima." << endl; }
    
}