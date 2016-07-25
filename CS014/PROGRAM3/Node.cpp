
#include "Node.h"

using namespace std;

Node::Node(string _data) : small(_data), left(0), middle (0), right(0), parent(0), small_count(1), large_count(0){}

bool Node::isTwoNode() {
    if (!small.empty() && large.empty() ) {
        return true;
    } else {
        return false;
    }
}
bool Node::isThreeNode() {
    if (!small.empty() && !large.empty() ) {
        return true;
    } else {
        return false;
    }
}

