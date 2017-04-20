#include <iostream>

using namespace std;

int f(int x) {
    if (x>2) {
        cout << "recursing, x = " << x << " ";
        return f(x-2)+f(x-3);
        
    }
    cout << endl << "Successful recursion." << endl;
    return x;
    }
    
int * min (int arr[], int size) {
    if (size == 0) {
        return 0;
    }
    if (size == 1) {
        return &arr[0];
    }
    if (arr[0]>arr[size]) {
        arr[0]=arr[size];
    }
    return min(arr,size-1);
}

int main() {
    int *p1 = new int(100);
    int *p2 = new int(200);
    cout << *p1 << " " << *p2 << endl;
    
    p1 = p2;
    cout << *p1 << " " << *p2 << endl;
    
    *p1 = 300;
    cout << *p1 << " " << *p2 << endl;
    
    *p2 = 400;
    cout << *p1 << " " << *p2 << endl;
    
    delete p1,p2;
    
    char *cp = new char;
    *cp = 'c';
    cout << *cp << endl;
    
    delete cp;
    
    cout << f(8) << endl;
    
    int arr[10] =  { 112, 123, 1, 3143, 1243, 1, 1231, 412, 141, 92 }; 
    int *ptr = 0;
    ptr = min(arr,10);
    cout << "Min value is: " << *ptr << endl;
    
    return 0;
}