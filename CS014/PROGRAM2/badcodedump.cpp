void BinarySearchTree::remove_node(Node* node) { // actually delete a node
    // there are five cases. case 0 is an empty tree, which is handled above.
    Node *swapNode;
    //case 1: a leaf, simply delete it
    if (node->left == 0 && node->right == 0) {
        if (node->data < node->up->data) {
            // then this is the right child and a leaf
            node->up->right = 0;
            delete node;
        } else {
            // then it must be the left child
            node->up->left = 0;
            delete node;
        }
    
    // case 2: a node with one left child
    } else if (node->left != 0 && node->right == 0) {
        cout << "Node with one left child." << endl;
        if (node->data < node->up->data) {
            // then node is the right child of parent
            node->up->right = node->left;
            delete node;
        } else {
            // then it must be the left child of parent
            node->up->left = node->left;
            delete node;    
        }
    
    // case 3: a node with one right child
    } else if (node->left == 0 && node->right != 0) {
        cout << "Node with one right child." << endl;  
        swapNode = minNode(node->right); 	// minNode here is identifying the lowest-valued right child of the node to be removed.
        node->data = swapNode->data;		// replace the node to be removed's data and count with the minNode	
        node->count = swapNode->count;
        cout << "The minimum node was " << node->data << " (" << node->count << ")" << endl;
        if (swapNode->data > swapNode->up->data) {
            // then this was a right child
            swapNode->up->right = 0;
            delete swapNode;
        } else if (swapNode->data < swapNode->up->data) {
            // then this was a left child
            swapNode->up->left = 0;
            delete swapNode;
        }
        
    // case 4: a node with two children
    } else if (node->left != 0 && node->right != 0) {
        cout << "Node with two children." << endl;
        // copy all data from right child into this node
        // recursively call remove on right child
        node->data = node->right->data;
        node->count = node->right->count;
        remove_node(node->right);
        delete node;
    }
}

/*
golf
oscar
foxtrot
papa
alpha
india
mike
juliet
quebec
bravo
epsilon
india
delta
alpha
hotel
charlie
lima
kilo
india
*/