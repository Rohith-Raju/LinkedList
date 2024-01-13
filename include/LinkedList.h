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
public:
    Node* head;
    Node* tail;
    LinkedList();
    LinkedList(std::initializer_list<T>list);
    void insert_first(Node* node);
    bool is_empty();
    void push_back(T data);
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
    if(pos > size()) throw std::out_of_range("Index out of bounds");
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

#endif //TEMPLATED_ALGORITHMS_LINKEDLIST_H
