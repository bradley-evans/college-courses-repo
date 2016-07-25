#include <iostream>

using namespace std;


void enqueue (const Object &o) {
    
    if (rear < maxsize && rear > front) {
        rear++;
        queue[rear] = o
    }
}

Object dequeue () {
    
    Object temp;
    
    temp = queue[front];
    if (front < rear) {
        // standard case, front behind rear
        front++;
    } else if (front < maxsize && rear != 0) {
        front = 0;
    } else if (front == rear) {
        // list is empty
    }
    
    return temp;
}

int main() {
    
    
    
    
    
    
    
}

void dequeue () {
    if (front != rear) {
        Data data = front->data
        this->front = front->next;
        delete front->next;
        delete front->
        
    }   
}