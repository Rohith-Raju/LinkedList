//
// Created by Rohith on 1/3/24.
//

#ifndef CPPTEMPLATION_LINKEDLIST_H
#define CPPTEMPLATION_LINKEDLIST_H

#include <initializer_list>
#include <stdexcept>

template <class T> class LinkedList {
private:
  struct Node {
    T data;
    Node *next;
    Node(T data) {
      this->data = data;
      next = nullptr;
    };
  };
  size_t size_counter = 0;

public:
  Node *head;
  Node *tail;

  class forward_it;
  class reverse_it;

  /* Type definations */
  typedef LinkedList<T> __self;
  typedef typename LinkedList<T>::Node node_type;
  typedef T value_type;
  typedef T &refernece;
  typedef T *pointer;
  typedef forward_it iterator;
  typedef reverse_it reverse_iterator;

  // Default constructor
  LinkedList();

  // Constructor with initlaizer list
  LinkedList(std::initializer_list<T> list);

  // Copy constructor
  LinkedList(LinkedList &other);

  // Move constructor
  LinkedList(LinkedList &&other);

  // Destructor
  ~LinkedList();

  /* Iterators */
  iterator begin();
  iterator end();

  reverse_iterator rbegin();
  reverse_iterator rend();

  /* Mutator methods */
  void reverse();
  void insert_first(Node *node);
  void push_back(T data);

  /* Getters */
  T get_head_val();
  T get_tail_val();
  Node *at(size_t pos);
  size_t size();

  /* Merge sort and helper */
  LinkedList<T> &sort();
  template <class function> LinkedList<T> &sort(function &&func);

  LinkedList<T>::Node *middle(LinkedList<T>::Node *head);
  LinkedList<T> split(LinkedList<T>::Node *);
  template <class function>
  LinkedList<T> &merge(LinkedList<T> &list, function &&func);

  template <class function>
  LinkedList<T>::Node *merge_sort(Node *left, Node *right, function &&func);
  void deep_clean(Node *&list);
  LinkedList<T> &clean();

  /* Genaral purpose  */
  bool is_empty();
  bool delete_at(size_t pos);

  /* LinkedList operator overloads */
  bool operator==(LinkedList<T> &right);
  bool operator!=(LinkedList<T> &right);
  Node *operator[](size_t pos);

  class forward_it {
  protected:
    Node *pointer;

  public:
    typedef forward_it __self;

    forward_it(Node *ptr = nullptr) : pointer(ptr) {}

    /* Comparison operators */
    virtual bool operator==(__self other);
    virtual bool operator!=(__self other);

    /* Operator overloads */
    __self &operator++();   // prefix
    __self operator++(int); // postfix
    T &operator*();
    T *operator->();
  };

  class reverse_it : public forward_it {
  private:
    LinkedList<T> *list = nullptr;

  public:
    typedef reverse_it __self;

    reverse_it(LinkedList<T> *list) : forward_it(list->head) {
      this->list = list;
    }

    reverse_it() : forward_it(nullptr) {}

    ~reverse_it() {
      if (list != nullptr) {
        list->clean();
        delete list;
      }
    }
  };
};

/* LinkedList implementation starts from here */

template <typename T> typename LinkedList<T>::iterator LinkedList<T>::begin() {
  return iterator(head);
}

template <typename T> typename LinkedList<T>::iterator LinkedList<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename LinkedList<T>::reverse_iterator LinkedList<T>::rbegin() {
  LinkedList<T> *temp = new LinkedList<T>(*this);
  temp->reverse();
  return reverse_iterator(temp);
}

template <typename T>
typename LinkedList<T>::reverse_iterator LinkedList<T>::rend() {
  return reverse_it();
}

/******** Constructors *************/

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list) : LinkedList() {
  for (T element : list) {
    push_back(element);
  }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList &other) : LinkedList() {
  for (T element : other) {
    push_back(element);
  }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList &&other) : LinkedList() {
  for (T element : other) {
    push_back(element);
  }
  other.clean();
  other.head = nullptr;
  other.tail = nullptr;
}

template <typename T> LinkedList<T>::~LinkedList() { clean(); }

template <typename T> LinkedList<T> &LinkedList<T>::clean() {
  if (is_empty()) {
    return *this;
  }

  // clear_list is a recursive function that deletes each node of the list
  deep_clean(head);

  tail = nullptr;

  return *this;
}

/*
 * reverse() reverses all the elements where head = prev_tail
 * and  tail = prev_head
 */

template <typename T> void LinkedList<T>::reverse() {
  Node *first_ptr = nullptr;
  Node *second_ptr = head;
  while (second_ptr != nullptr) {
    Node *temp = second_ptr->next;
    second_ptr->next = first_ptr;
    first_ptr = second_ptr;
    second_ptr = temp;
  }
  tail = head;
  head = first_ptr;
}

/*
 * deep_clean() drills into the entire list and removes all the elements
 */
template <typename T> void LinkedList<T>::deep_clean(Node *&list) {
  if (list != tail) {
    deep_clean(list->next);
  }
  delete list;
  list = nullptr;
  this->size_counter--;
  return;
}

/*
 * insert_first() inserts element only when there are no elements in the list
 */
template <typename T> void LinkedList<T>::insert_first(Node *node) {
  if (!is_empty()) {
    head = node;
    size_counter = 1;
    if (tail == nullptr) {
      tail = head;
    }
  }
  return;
}

/*
 * is_empty() returns true if the list is empty
 */
template <typename T> bool LinkedList<T>::is_empty() { return head == nullptr; }

/*
 * push_back() append new element to the end of the list
 */
template <typename T> void LinkedList<T>::push_back(T data) {
  Node *node = new Node(data);
  if (is_empty()) {
    insert_first(node);
    return;
  }
  size_counter++;
  tail->next = node;
  tail = node;
}
/*
 * size() returns the size of the list
 */
template <typename T> size_t LinkedList<T>::size() { return size_counter; }

/*
 * at() returns the node containing the data at a given position
 */
template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::at(size_t pos) {
  if (pos >= size())
    throw std::out_of_range("Index out of bounds");
  LinkedList<T>::Node *iterator = head;
  while (pos) {
    iterator = iterator->next;
    pos--;
  }
  return iterator;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::operator[](size_t pos) {
  return at(pos);
}

/*
 * delete_at() remove element in the given pos
 */
template <typename T> bool LinkedList<T>::delete_at(size_t pos) {
  if (pos >= size()) {
    throw std::out_of_range("Cannot delete. Index out of bounds");
    return false;
  }
  if (pos == 0) {
    Node *temp = head;
    head = head->next;
    size_counter--;
    delete temp;
    return true;
  }
  // stop at previous
  pos -= 1;
  Node *list = head;
  while (pos) {
    list = list->next;
    pos--;
  }
  if (list->next == tail) {
    Node *temp = tail;
    tail = list;
    size_counter--;
    delete temp;
    return true;
  } else {
    Node *temp = list->next;
    list->next = list->next->next;
    size_counter--;
    temp->next = nullptr;
    delete temp;
    return true;
  }
}

/*
 * get_head_val() return the value of head
 */
template <typename T> T LinkedList<T>::get_head_val() { return head->data; }

/*
 * get_tail_val() return the value of tail
 */
template <typename T> T LinkedList<T>::get_tail_val() { return tail->data; }

/*
 * sort() sorts all the elements in the list (default accending)
 */
template <typename T> LinkedList<T> &LinkedList<T>::sort() {
  return sort([](T leftVal, T rightVal) { return leftVal < rightVal; });
}

/*
 * sort() sorts all the elements in the list by passing in a anonymous function
 */

template <typename T>
template <class function>
LinkedList<T> &LinkedList<T>::sort(function &&func) {
  if (!head || !head->next)
    return *this;
  LinkedList<T> right_list = split(middle(head));
  sort(func);
  right_list.sort(func);
  return merge(right_list, func);
}

template <typename T>
template <class function>
LinkedList<T> &LinkedList<T>::merge(LinkedList<T> &list, function &&func) {
  head = merge_sort(head, list.head, func);
  // set tail to the greatest of the two lists
  if (!tail || (list.tail && func(tail->data, list.tail->data))) {
    tail = list.tail;
  }
  // remove the original list addresses
  list.head = nullptr;
  list.tail = nullptr;
  return *this;
}

template <typename T>
template <class function>
typename LinkedList<T>::Node *LinkedList<T>::merge_sort(Node *left, Node *right,
                                                        function &&func) {
  if (left == nullptr)
    return right;
  if (right == nullptr)
    return left;
  bool comp = func(left->data, right->data);
  Node *head = comp ? left : right;
  head->next = comp ? merge_sort(left->next, right, func)
                    : merge_sort(left, right->next, func);
  return head;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::middle(LinkedList<T>::Node *head) {
  if (head == nullptr || head->next == nullptr)
    return head;
  LinkedList<T>::Node *fast = head;
  LinkedList<T>::Node *slow = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}

template <typename T>
LinkedList<T> LinkedList<T>::split(LinkedList<T>::Node *node) {
  LinkedList<T> temporary;
  if (node != nullptr) {
    temporary.head = node->next;
    temporary.tail = temporary.head != nullptr ? tail : temporary.head;
    tail = node;
    tail->next = nullptr;
  }
  return temporary;
}

template <typename T> bool LinkedList<T>::operator==(LinkedList<T> &right) {

  // Compare sizes first
  if (size_counter != right.size_counter)
    return false;

  auto left_it = begin();
  auto right_it = right.begin();

  while (left_it != end() && right_it != end()) {
    // all the elements should match
    if (*(left_it++) != *(right_it++))
      return false;
  }
  return true;
}

template <typename T> bool LinkedList<T>::operator!=(LinkedList<T> &right) {
  !(*this == right);
}

/* Iterator Operations */

template <typename T> bool LinkedList<T>::forward_it::operator==(__self other) {
  return this->pointer == other.pointer;
}

template <typename T> bool LinkedList<T>::forward_it::operator!=(__self other) {
  return !(*this == other);
}

template <typename T>
typename LinkedList<T>::forward_it LinkedList<T>::forward_it::operator++(int) {
  __self temp = __self(this->pointer);
  ++(*this);
  return temp;
}

template <typename T>
typename LinkedList<T>::forward_it &LinkedList<T>::forward_it::operator++() {
  this->pointer = this->pointer->next;
  return *this;
}

template <typename T> T &LinkedList<T>::forward_it::operator*() {
  return this->pointer->data;
}
template <typename T> T *LinkedList<T>::forward_it::operator->() {
  return &this->pointer->data;
}

#endif // CPPTEMPLATION_LINKEDLIST_H
