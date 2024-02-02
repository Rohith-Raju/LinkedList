//
// Created by Rohith on 1/3/24.
//

#ifndef TEMPLATED_ALGORITHMS_LINKEDLIST_H
#define TEMPLATED_ALGORITHMS_LINKEDLIST_H

#include <initializer_list>
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node{
        T data;
        Node* next;
        Node(T data){
            this->data = data;
            next = nullptr;
        };
    };
    size_t size_counter = 0;
    LinkedList<T>::Node* middle(LinkedList<T>::Node* head);
    LinkedList<T> split(LinkedList<T>::Node*);
    template<class function>
            LinkedList<T>& merge(LinkedList<T> list, function &&func);

    template<class function>
            LinkedList<T>::Node* merge_sort(Node* left, Node* right, function &&func);

public:
    Node* head;
    Node* tail;
    LinkedList();
    LinkedList(std::initializer_list<T>list);
    void insert_first(Node* node);
    bool is_empty();
    void push_back(T data);
    LinkedList<T>& sort();
    template<class function>
            LinkedList<T>& sort(function&& func);
    T get_head();
    T get_tail();
    T at(size_t pos);
    size_t size();
    T operator[](size_t pos);
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T>list):LinkedList(){
    for(T element: list){
        push_back(element);
    }
}

template <typename T>
void LinkedList<T>::insert_first(Node* node) {
    head = node;
    size_counter = 1;
    if(tail == nullptr){
        tail = head;
    }
    return;
}

template <typename T>
bool LinkedList<T>::is_empty() {
    return head == nullptr;
}

template <typename T>
void LinkedList<T>::push_back(T data) {
    Node *node = new Node(data);
    if(is_empty()){
        insert_first(node);
        return;
    }
    size_counter++;
    tail->next = node;
    tail = node;
}

template <typename T>
size_t LinkedList<T>::size(){
    return size_counter;
}

template <typename T>
T LinkedList<T>::at(size_t pos) {
    if(pos >= size()) throw std::out_of_range("Index out of bounds");
    LinkedList<T>::Node* iterator = head;
    while (pos){
        iterator = iterator->next;
        pos--;
    }
    return iterator->data;
}

template <typename T>
T LinkedList<T>::operator[](size_t pos) {
    return at(pos);
}

template <typename T>
T LinkedList<T>::get_head() {
    return head->data;
}

template <typename T>
T LinkedList<T>::get_tail() {
    return tail->data;
}
template <typename T>
LinkedList<T>&  LinkedList<T>::sort() {
return sort([](T leftVal, T rightVal){ return leftVal < rightVal;});
}

template <typename T>
template <class function>
LinkedList<T>& LinkedList<T>::sort(function&& func) {
    if(!head || !head->next) return *this;
    LinkedList<T> right_list  = split(middle(head));
    sort(func);
    right_list.sort(func);
    return merge(right_list,func);
}

template <typename T>
template <class function>
LinkedList<T>&
LinkedList<T>::merge(LinkedList<T> list, function &&func) {
    head = merge_sort(head, list.head, func);
    //set tail to the greatest of the two lists
    if(!tail || (list.tail && func(tail->data,list.tail->data))){
        tail = list.tail;
    }
    return *this;
}


template <typename T>
template <class function>
LinkedList<T>::Node*
LinkedList<T>::merge_sort(Node* left, Node* right, function &&func) {
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    bool comp = func(left->data, right->data);
    Node* head = comp ? left: right;
    head->next = comp ? merge_sort(left->next, right, func):
                 merge_sort(left,right->next,func);
    return head;
}


template <typename T>
LinkedList<T>::Node* LinkedList<T>::middle(LinkedList<T>::Node* head) {
    if(head == nullptr || head->next == nullptr) return head;
    LinkedList<T>::Node* fast = head;
    LinkedList<T>::Node* slow = head;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

template <typename T>
LinkedList<T> LinkedList<T>::split(LinkedList<T>::Node * node) {
    LinkedList<T> temporary;
    if(node != nullptr){
        temporary.head = node->next;
        temporary.tail = temporary.head != nullptr ? tail : temporary.head;
        tail = node;
        tail->next = nullptr;
    }
    return temporary;
}

//todo: write clean up funcs

#endif //TEMPLATED_ALGORITHMS_LINKEDLIST_H
