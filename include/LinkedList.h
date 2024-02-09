//
// Created by Rohith on 1/3/24.
//

#ifndef CPPTEMPLATION_LINKEDLIST_H
#define CPPTEMPLATION_LINKEDLIST_H

#include <initializer_list>
#include <stdexcept>

template <class T>
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
    void deep_clean(Node*& list);
    LinkedList<T>& clean();

public:
    Node* head;
    Node* tail;

    LinkedList();
    LinkedList(std::initializer_list<T>list);
    ~LinkedList();

    void insert_first(Node* node);
    bool is_empty();
    void push_back(T data);
    LinkedList<T>& sort();
    template<class function>
            LinkedList<T>& sort(function&& func);
    bool delete_at(size_t pos);
    T get_head_val();
    T get_tail_val();
    Node* at(size_t pos);
    size_t size();
    Node* operator[](size_t pos);
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
LinkedList<T>::~LinkedList() {
   //clean();
}

template <typename T>
LinkedList<T>& LinkedList<T>::clean(){
    if(is_empty())
    {
        return *this;
    }

    // clear_list is a recursive function that deletes each node of the list
    deep_clean(head);

    tail = nullptr;

    return *this;

}

template <typename T>
void  LinkedList<T>::deep_clean(Node*& list) {
    if(list != tail){
        deep_clean(list->next);
    }
    delete list;
    list = nullptr;
    this->size_counter--;
    return;
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
typename LinkedList<T>::Node*
LinkedList<T>::at(size_t pos) {
    if(pos >= size()) throw std::out_of_range("Index out of bounds");
    LinkedList<T>::Node* iterator = head;
    while (pos){
        iterator = iterator->next;
        pos--;
    }
    return iterator;
}

template <typename T>
typename LinkedList<T>::Node*
LinkedList<T>::operator[](size_t pos) {
    return at(pos);
}

template <typename T>
bool LinkedList<T>::delete_at(size_t pos) {
    if(pos >= size()){
        throw std::out_of_range("Cannot delete. Index out of bounds");
        return false;
    }
    if(pos == 0){
        Node* temp = head;
        head = head->next;
        size_counter--;
        delete temp;
        return true;
    }
    //stop at previous
    pos -= 1;
    Node* list = head;
    while (pos){
    list = list->next;
    pos--;
    }
    if(list->next == tail){
        Node* temp = tail;
        tail = list;
        size_counter--;
        delete temp;
        return true;
    }
    else{
        Node* temp = list->next;
        list->next = list->next->next;
        size_counter--;
        temp->next = nullptr;
        delete temp;
        return true;
    }
}

template <typename T>
T LinkedList<T>::get_head_val() {
    return head->data;
}

template <typename T>
T LinkedList<T>::get_tail_val() {
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
typename LinkedList<T>::Node*
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
typename LinkedList<T>::Node*
LinkedList<T>::middle(LinkedList<T>::Node* head) {
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
#endif //CPPTEMPLATION_LINKEDLIST_H
