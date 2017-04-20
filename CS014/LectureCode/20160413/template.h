#ifndef TEMPLATE_H
#define TEMPLATE_H

template <class T>
class List{
    private:
        Node<T> *head;
        Note<T> *tail;
    public:
        void pushFront(const T &);
        void pushBack(const T &);
        void remove(const T &);
}

template <class T>
void List<T>::pushFront (const T &a) {
    Node<T> *ptr = new Node<T>;
    ptr->item=a;
    ptr->next=head;
    head=ptr;
    if (!tail) {
        tail = ptr;
    }
}

template <class T>
void List<T>::pushBack (const T &a) {
    Node<T> *newNode = new Node<t>;
    Node<T> *currNode;
    
    newNode->item = a;
    currNode = tail;
    currNode->next = newNode;
    tail = newNode;
}
    
template <class T>
void List<T>::remove(const T &a) {
    if (head == 0) {return;}
    if (head->item == a) {
        Node<T> *del = head;
        head = head->next
        delete del;
    }
    if (head == 0) {tail = 0;}
}



#endif