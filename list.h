#include <functional>

using std::function;

#pragma once

template<class T>
class List {
public:

  class Node {
    List<T> *list;
    Node *prev, *next;
    T value;

  protected:

    Node(Node* prev, Node* next, T value, List<T>* list) : 
      prev(prev), next(next), value(value), list(list) {

      if (prev)
        prev->next = this;
      else
        list->tail = this;
      
      if (next)
        next->prev = this;
      else
        list->head = this;

      list->count++;
    }

    ~Node() {
      if (prev)
        prev->next = next;
      else
        list->tail = next;

      if (next)
        next->prev = prev;
      else
        list->head = prev;
        
      list->count--;
    }

  public:
    
    T getValue() {
      return value;
    }

    void setValue(T value) {
      this->value = value;
    }

    Node* addNext(List<T>* list, T value) {
      return new Node(this, this->getNext(), value, list);
    }

    Node* addPrev(List<T>* list, T value) {
      return new Node(this->getPrev(), this, value, list);
    }

    Node* getNext() {
      if (this == nullptr)
        return nullptr;

      return this->next;
    }

    Node* getPrev() {
      if (this == nullptr)
        return nullptr;
      
      return this->prev;
    }

    void remove() {
      if (this == nullptr)
        return;

      delete this;
    }

  };

protected:

  Node *tail = nullptr, *head = nullptr;
  int count = 0;

public:

  typedef function<bool (T)> searchBy;

  List() {}

  Node* addHead(T value) {
    return head->addNext(this, value);
  }

  Node* addTail(T value) {
    return tail->addPrev(this, value);
  }

  Node* getHead() {
    return head;
  }

  Node* getTail() {
    return tail;
  }

  int getCount() {
    return count;
  }

  Node* find(searchBy func) {
    for(auto n = tail; n != nullptr; n = n->getNext()) {
      if (func(n->getValue()))
        return n;
    }

    return nullptr;
  }

  Node* findByValue(T value) {
    for(auto n = tail; n != nullptr; n = n->getNext()) {
      if (n->getValue() == value)
        return n;
    }

    return nullptr;
  }

  bool remove(searchBy func) {
    Node* node = find(func);

    if (node == nullptr)
      return false;
    
    node->remove();
    return true;
  }

  bool removeByValue(T value) {
    Node* node = findByValue(value);

    if (node == nullptr)
      return false;
    
    node->remove();
    return true;
  }

};