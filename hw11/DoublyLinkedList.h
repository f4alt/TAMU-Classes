#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList();
    DoublyLinkedList(T);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; };
    T& front() { return head->data; };
    const T& front() const { return head->data; };
    T& back() { return tail->data; };
    const T& back() const { return tail->data; };
    void push_back(T);
    void push_front(T);
    // void pop_back();
    // void pop_front();
    // void erase(unsigned int);
    // void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    // template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // dO nOt CHanGe oRdEriNg.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  this->head = nullptr;
  this->tail = nullptr;
  this->sz = 0;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) {
  this->head->data = data;
  this->tail->data = data;
  this->sz = 1;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& tocopy): head(nullptr), tail(nullptr), sz(0) {
  Node<T>* current = tocopy.head;
  while (current) {
    this->push_back(current->data);
    current = current->next;
  }
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& tocopy) {
  Node<T>* current = tocopy.head;
  while (current) {
    this->push_back(current->data);
    current = current->next;
  }
  return* this;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template<typename T>
void DoublyLinkedList<T>::push_back(T elem) {
  Node<T>* node = new Node<T>(elem);
  if (!head) {
      // empty list
      head = node;
      tail = node;
      sz = 1;
  } else {
      // non empty list
      tail->next = node;
      node->prev = tail;
      tail = node;
      sz++;
  }
}

template<typename T>
void DoublyLinkedList<T>::push_front(T elem) {
  Node<T>* node = new Node<T>(elem);
  if (!head) {
    head = node;
    tail = node;
    sz = 1;
  } else {
    head->prev = node;
    node->next = head;
    head = node;
    sz++;
  }
}

template<typename T>
void DoublyLinkedList<T>::clear() {
  Node<T>* current = head;
   while (current) {
    Node<T>* next = current->next;
    delete current;
    current = next;
  }
  sz = 0;
  head = nullptr;
  tail = nullptr;
}

template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
    // getting you started on this once... definition for this overloaded operator will go here.
    return true;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

#endif
