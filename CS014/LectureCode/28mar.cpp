#include <list>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    
    list<int> l1;
    for (unsigned i=0; i<30; i++)  {
        l1.push_back(i);
    }
    
    // we can't access the pointers in head directly
    // because these are private data members. so, we
    // use a public member iterator to iterate through
    // the list. x.begin() will return the first member
    // of the list.
    
    // ++ is overloaded in the iterator to allow for
    // incrementation. the next integer in memory is
    // not necessarily the next data member.
    list<int>::iterator it;
    for (it = l1.begin(); it != l1.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
    
    for (it=l1.begin();it!=l1.end();++it) {
        if (*it % 2 == 0) {
            it = l1.erase(it);
        }
    }

    for (it = l1.begin(); it != l1.end(); ++it) {
        cout << *it << ' ';
    }
    
}