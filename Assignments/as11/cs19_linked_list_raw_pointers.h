/**
 * @file cs19_linked_list_raw_pointers.h
 * @author Stephanie L'Heureux (salhaureux)
 * @date 11/19/22
 *
 * A class named LinkedList in namespace cs19 that represents a
 * doubly linked list using raw pointers, with many functions
 * similar to those of std::list
 */
#ifndef CS19_LINKED_LIST_RAW_POINTERS_H_
#define CS19_LINKED_LIST_RAW_POINTERS_H_

#include <initializer_list>
#include <iostream>

namespace cs19 {
template <typename T>
class LinkedList {
  struct Node;

 public:
  LinkedList() {}

  LinkedList(std::initializer_list<T> init_list) {
    for (const auto& val : init_list) {
      this->push_back(val);
    }
  }

  LinkedList(const LinkedList<T>& another) {
    for (Node* cur = another.head_; cur; cur = cur->next) {
      this->push_back(cur->data);
    }
  }

  ~LinkedList() {
    while (this->head_) {
      Node* old_head = this->head_;
      this->head_ = old_head->next;
      delete old_head;
    }
  }

  T& back() const {
    if (this->size_ == 0) {
      throw std::domain_error("List is empty");
    }
    return this->tail_->data;
  }

  bool empty() const { return !(this->size_); }

  T& front() const {
    if (this->size_ == 0) {
      throw std::domain_error("List is empty");
    }
    return this->head_->data;
  }

  bool operator!=(const LinkedList<T>& another) {
    if (another.size() != this->size_) return true;
    Node* orig = this->head_;
    Node* other = another.head_;
    while (orig) {
      if (other->data != orig->data) return true;
      orig = orig->next;
      other = other->next;
    }
    return false;
  }

  //  for (Node* orig = this->head_, other = another.head_; orig; orig =
  //  orig->next, other = other->next) {
  //    if (orig != other) return true;
  //  }

  LinkedList& operator=(const LinkedList<T>& another) {
    this->clear();
    for (Node* other = another.head_; other; other = other->next) {
      this->push_back(other->data);
    }
    return *this;
  }

  LinkedList& operator=(std::initializer_list<T> init_list) {
    this->clear();
    for (const auto& val : init_list) {
      this->push_back(val);
    }
    return *this;
  }

  bool operator==(const LinkedList<T>& another) {
    if (another.size() != this->size_) return false;
    Node* orig = this->head_;
    Node* other = another.head_;
    while (orig) {
      if (other->data != orig->data) return false;
      orig = orig->next;
      other = other->next;
    }
    return true;
  }

  void pop_back() {
    if (this->size_ == 0) {
      throw std::domain_error("List is empty");
    }
    Node* old_tail = this->tail_;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->tail_ = this->tail_->prev;
      this->tail_->next = nullptr;
    }
    --this->size_;
    delete old_tail;
  }

  void pop_front() {
    if (this->size_ == 0) {
      throw std::domain_error("List is empty");
    }
    Node* old_head = this->head_;
    if (this->size_ == 1) {
      this->head_ = this->tail_ = nullptr;
    } else {
      this->head_ = this->head_->next;
      this->head_->prev = nullptr;
    }
    --this->size_;
    delete old_head;
  }

  void push_back(const T& val) {
    Node* new_node = new Node{val};
    if (this->size_) {
      this->tail_->next = new_node;
      new_node->prev = this->tail_;
      this->tail_ = new_node;
    } else {
      this->head_ = this->tail_ = new_node;
    }
    ++this->size_;
  }

  void push_front(const T& val) {
    Node* new_node = new Node{val};
    if (this->size_) {
      new_node->next = this->head_;
      this->head_->prev = new_node;
      this->head_ = new_node;
    } else {
      this->head_ = this->tail_ = new_node;
    }
    ++this->size_;
  }

  void remove(const T& val) {
    if (this->size_ > 2) {
      Node* cur = this->head_->next;
      while (cur != this->tail_) {
        if (cur->data == val) {
          Node* old = cur;
          cur->next->prev = cur->prev;
          cur->prev->next = cur->next;
          cur = cur->next;
          --this->size_;
          delete old;
        } else {
          cur = cur->next;
        }
      }
    }
    if (this->size_ != 0) {
      if (this->head_->data == val) this->pop_front();
      if (this->tail_->data == val) this->pop_back();
    }
  }

  void resize(std::size_t n) {
    T val;
    while (this->size_ > n) {
      this->pop_back();
    }
    while (this->size_ < n) {
      this->push_back(val);
    }
  }

  void resize(std::size_t n, const T& fill_value) {
    while (this->size_ > n) {
      this->pop_back();
    }
    while (this->size_ < n) {
      this->push_back(fill_value);
    }
  }

  void clear() {
    while (this->size_ > 0) {
      this->pop_back();
    }
  }

  void reverse() {
    Node* cur = this->head_;
    while (cur) {
      Node* next = cur->next;
      cur->next = cur->prev;
      cur->prev = next;
      cur = next;
    }
    Node* temp = this->tail_;
    this->tail_ = this->head_;
    this->head_ = temp;
  }

  std::size_t size() const { return this->size_; }

  void unique() {
    if (this->size_ == 0) return;
    Node* cur = this->head_->next;
    while (cur) {
      Node* prev = cur->prev;
      if (cur->data == prev->data) {
        if (cur == this->tail_) {
          cur = cur->next;
          this->pop_back();
        } else {
          Node* old = cur;
          cur->next->prev = cur->prev;
          cur->prev->next = cur->next;
          cur = cur->next;
          --this->size_;
          delete old;
        }
      } else {
        cur = cur->next;
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& out,
                                  const LinkedList<T>& list) {
    out << '[';
    for (Node* cur = list.head_; cur; cur = cur->next) {
      out << cur->data;
      if (cur->next) out << ", ";
    }
    out << ']';
    return out;
  }

 private:
  struct Node {
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;
};
}  // namespace cs19

#endif  // CS19_LINKED_LIST_RAW_POINTERS_H_