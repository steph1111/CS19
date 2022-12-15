/**
 * @file cs19_linked_list_raw_pointers_iterable.h
 * @author Stephanie L'Heureux (steph1111)
 * @date 11/28/22
 *
 * Class that emulates a std::list
 * Documentation:
 * http://jeff.cis.cabrillo.edu/datasets/docs_cs19_linked_list_raw_pointers_iterable/classcs19_1_1LinkedList.html
 */
#ifndef CS19_LINKED_LIST_RAW_POINTERS_ITERABLE_H_
#define CS19_LINKED_LIST_RAW_POINTERS_ITERABLE_H_

#include <initializer_list>
#include <iostream>

// FIXME: Possible seg fault on splice() (4)
// FIXME: Incorrect return values on erase() 

namespace cs19 {
template <typename T>
class LinkedList {
  struct Node;
  class Iterator;

 public:
  LinkedList() {}
  /**
   * Constructs a LinkedList from an std::initializer_list
   * 
   * @param init_list The initializer list construct a LinkedList from
   */
  LinkedList(std::initializer_list<T> init_list) {
    for (const auto& val : init_list) {
      this->push_back(val);
    }
  }

  /**
   * Constructs a LinkedList from another LinkedList
   * 
   * @param another Another LinkedList construct a LinkedList from
   */
  LinkedList(const LinkedList<T>& another) {
    for (Node* cur = another.head_; cur; cur = cur->next) {
      this->push_back(cur->data);
    }
  }

  /**
   * Constructs a list with as many elements as the range [first,last), with
   * each element constructed from its corresponding element in 
   * that range, in the same order.
   * 
   * @param first Iterator to start from (inclusive)
   * @param last Iterator to end with (exclusive/past the end)
   */
  template <typename InputIterator>
  LinkedList(InputIterator first, InputIterator last) {
    for (; first != last; ++first) this->push_back(*first);
  }

  /**
   * Distructor for a LinkedList object. Deletes all new nodes
   */
  ~LinkedList() {
    while (this->head_) {
      Node* old_head = this->head_;
      this->head_ = old_head->next;
      delete old_head;
    }
  }

  /**
   * Returns a reference to the value in the last element in this list.
   * 
   * @return the last element in the LinkedList
   */
  T& back() const {
    if (this->size_ == 0) {
      throw std::domain_error("List is empty");
    }
    return this->tail_->data;
  }

  /**
   * Returns whether the list container is empty
   * 
   * @return true if the size is 0, else false
   */
  bool empty() const { return !(this->size_); }

  /**
   * Returns a reference to the value in the first element in this list.
   * 
   * @return the first element in the LinkedList
   */
  T& front() const {
    if (this->size_ == 0) {
      throw std::domain_error("List is empty");
    }
    return this->head_->data;
  }

  /**
   * Replaces the contents of this list with a copy of each element 
   * in 'another', in the same order.
   * 
   * @param another the LinkedList from which to copy
   */
  LinkedList& operator=(const LinkedList<T>& another) {
    this->clear();
    for (Node* other = another.head_; other; other = other->next) {
      this->push_back(other->data);
    }
    return *this;
  }

  /**
   * Replaces the contents of this list with a copy of each element 
   * in 'init_list', in the same order.
   * 
   * @param another the std::initializer_list from which to copy
   */
  LinkedList& operator=(std::initializer_list<T> init_list) {
    this->clear();
    for (const auto& val : init_list) {
      this->push_back(val);
    }
    return *this;
  }

  /**
   * Compares this list with 'another' for inequality.
   * 
   * @return whether the two lists do not contain the same number of 
   * elements, with the same values, in the same order
   */
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

  /**
   * Compares this list with another for equality.
   * 
   * @return whether the two lists contain the same number of 
   * elements, with the same values, in the same order
   */
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

  /**
   * Deletes the last value in this list.
   */
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

  /**
   * Deletes the first value in this list.
   */
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

  /**
   * Appends a new element to this list, after its current last element.
   * 
   * @param val the value to be copied to the appended element
   */
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

  /**
   * Prepends a new element to this list, before its current first element.
   * 
   * @param val the value to be copied to the prepended element
   */
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

  /**
   * Removes from the container all the elements that compare equal to 'val'.
   * 
   * @param val	value of the elements to be removed
   */
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

  /**
   * Resizes the list so that it contains n elements.
   * 
   * If 'n' is smaller than the current list size, the content is reduced to its 
   * first 'n' elements, removing those beyond (and destroying them). If 'n' is 
   * greater than the current list size, the content is expanded by inserting 
   * at the end as many elements as needed to reach a size of 'n'.
   * 
   * @param n the new size for the list
   */
  void resize(std::size_t n) {
    T val;
    while (this->size_ > n) {
      this->pop_back();
    }
    while (this->size_ < n) {
      this->push_back(val);
    }
  }

  /**
   * Resizes the list so that it contains n elements.
   * 
   * If 'n' is smaller than the current list size, the content is reduced to its 
   * first 'n' elements, removing those beyond (and destroying them). If 'n' is 
   * greater than the current list size, the content is expanded by inserting 
   * at the end as many elements as needed to reach a size of 'n'.
   * 
   * @param n the new size for the list
   * @param fill_value	the value to place in any new elements
   */
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

  /**
   * Reverses the order of the elements in this list. 
   * No element is created nor destroyed.
   */
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

  /**
   * Returns the number of elements in this list 
   * 
   * @return The number of elements in this list
   */
  std::size_t size() const { return this->size_; }

  /**
   * Removes duplicate values in order from this list.
   */
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

  /**
  * Returns an iterator pointing to the first element in this list.
  *
  * @return An iterator to the beginning of the sequence.
  */
  Iterator begin() {
    Iterator it(this->head_, this->tail_);
    return it;
  }

  /**
   * Returns an iterator referring to the past-the-end element in this
   * list.
   *
   * @return An iterator to the element past the end of the sequence.
   */
  Iterator end() {
    Iterator it(nullptr, this->tail_);
    return it;
  }

  /**
   * Extends this list by inserting a new element before the element at the
   * specified position.
   *
   * @param position Position in the list where the new element is inserted.
   * @param val Value to be copied to the inserted element.
   * @return An iterator that points to the newly inserted element.
   */
  Iterator insert(Iterator position, const T& val) {
    Node* cur = position->get_cur();
    Node* temp = nullptr;
    if (cur != nullptr) {
      if (cur->prev == nullptr) {
        this->push_front(val);
      } else {
        Node* new_node = new Node{val};
        temp = cur->prev;
        cur->prev = new_node;
        temp->next = new_node;
        new_node->next = cur;
        new_node->prev = temp;
        ++this->size_;
      }
      return --position;
    } else {
      this->push_back(val);
      return --this->end();
    }
  }

  /**
   * Extends this list by inserting new elements before the element at the
   * specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param n Number of elements to insert. Each element is initialized to a
   * copy of `val`.
   * @param val Value to be copied to the inserted elements.
   * @return An iterator that points to the first of the newly inserted
   * elements.
   */
  Iterator insert(Iterator position, std::size_t n, const T& val) {
    Iterator return_val = position;

    for (int i = 0; i < n; i++) {
      if (i == 0) {
        return_val = this->insert(position, val);
      } else {
        this->insert(position, val);
      }
    }

    return return_val;
  }

  /**
   * Extends this list by inserting new elements in the range [first,last)
   * before the element at the
   * specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param first An iterator that points to the first value to be inserted.
   * @param last An iterator that points to the value after the last value to be
   * inserted.
   * @return An iterator that points to the first of the newly inserted
   * elements.
   */
  template <typename InputIterator>
  Iterator insert(Iterator position, InputIterator first, InputIterator last) {
    Iterator return_val = position;

    for (auto it = first; it != last; it++) {
      if (it == first) {
        return_val = this->insert(position, *it);
      } else {
        this->insert(position, *it);
      }
    }

    return return_val;
  }

  /**
   * Extends this list by inserting new elements from an initializer list at the
   * specified position.
   *
   * @param position Position in the list where the new elements are inserted.
   * @param init_list The list of values to be inserted.
   * @return An iterator that points to the first of the newly inserted
   * elements.
   */
  Iterator insert(Iterator position, std::initializer_list<T> init_list) {
    return this->insert(position, init_list.begin(), init_list.end());
  }

  /**
   * Removes from this list a single element at the specified position.
   *
   * @param position Iterator pointing to a single element to be removed from
   * the list.
   * @return An iterator pointing to the element that followed the last element
   * erased by the
   * function call. This is the list end if the operation erased the last
   * element in the
   * sequence.
   */
  Iterator erase(Iterator position) {
    Node* cur = position.get_cur();
    Iterator temp_itr = position;

    if (cur->prev == nullptr) {
      temp_itr++;
      this->pop_front();
      return temp_itr;
    } else if (cur->next == nullptr) {
      this->pop_back();
      return --this->end();
    } else {
      temp_itr++;
      Node* old = cur;
      cur->next->prev = cur->prev;
      cur->prev->next = cur->next;
      cur = cur->next;
      --this->size_;
      delete old;
      return temp_itr;
    }
  }

  /**
   * removes from this list a range of elements (`[first,last)`).
   *
   * @param first An iterator that points to the first value to be removed.
   * @param last An iterator that points to the value after the last value to be
   * removed.
   * @return An iterator pointing to the element that followed the last element
   * erased by the
   * function call. This is the list end if the operation erased the last
   * element in the sequence.
   */
  Iterator erase(Iterator first, Iterator last) {
    Iterator return_val = last;
    for (auto it = first; it != last; it++) {
      return_val = this->erase(it);
    }
    return return_val;
  }

  /**
   * Transfers all elements from another list into this list,
   * inserting them at `position`. The operation does not
   * involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the position
   * in this list where elements are inserted.
   * @param that The list from which to copy elements.
   */
  void splice(Iterator position, LinkedList& that) {
    Node* cur = position->get_cur();
    Node* temp = nullptr;

    if (cur != nullptr) {          // not at end
      if (cur->prev == nullptr) {  //  at the beginning
        that.tail_->next = cur;
        this->head_->prev = that.tail_;
        this->head_ = that.head_;
      } else {  // in middle
        temp = cur->prev;
        cur->prev = that.tail_;
        temp->next = that.head_;
        that.tail_->next = cur;
        that.head_->prev = temp;
      }
    } else {  // at the end
      that.head_->prev = cur;
      this->tail_->next = that.head_;
      this->tail_ = that.tail_;
    }
    this->size_ += that.size_;
    that.head_ = nullptr;
    that.tail_ = nullptr;
    that.size_ = 0;
  }

  /**
   * Transfers one element from another list into this list, inserting it at
   * `position`. The
   * operation does not involve the construction or destruction of any element.
   *
   * @param position An iterator that points to the insertion position in this
   * list.
   * @param that The list from which to copy an element.
   * @param that_position An iterator that points to the element to transfer
   * from the other list to
   * this list.
   */
  void splice(Iterator position, LinkedList& that, Iterator that_position) {
    Node* pos = position->get_cur();
    Node* cur = that_position->get_cur();
    Node* cur_copy = that_position->get_cur();
    Node* temp = nullptr;

    if (cur_copy->prev == nullptr) {  // beginning of that
      that.head_ = that.head_->next;
      that.head_->prev = nullptr;
    } else if (cur_copy->next == nullptr) {  // end of that
      that.tail_ = that.tail_->prev;
      that.tail_->next = nullptr;
    } else {  // middle of that
      cur_copy->next->prev = cur_copy->prev;
      cur_copy->prev->next = cur_copy->next;
      cur_copy = cur_copy->next;
    }
    if (pos != nullptr) {          // not end of this
      if (pos->prev == nullptr) {  // beginning of this
        cur->next = this->head_;
        cur->prev = nullptr;
        this->head_->prev = cur;
        this->head_ = cur;
      } else {  // middle of this
        temp = pos->prev;
        pos->prev = cur;
        temp->next = cur;
        cur->next = pos;
        cur->prev = temp;
      }
    } else {  // end of this
      cur->prev = this->tail_;
      cur->next = nullptr;
      this->tail_->next = cur;
      this->tail_ = cur;
    }
    this->size_++;
    that.size_--;
  }

  /**
   * Transfers the range of elements `[first,last)` from another list into this
   * list, inserting it
   * at `position`. The operation does not involve the construction or
   * destruction of any element.
   *
   * @param position An iterator that points to the insertion position in this
   * list.
   * @param that The list from which to copy a range of elements.
   * @param first An iterator that points to the first value to be transferred.
   * @param last An iterator that points to the value after the last value to be
   * transferred.
   */
  void splice(Iterator position, LinkedList& that, Iterator first,
              Iterator last) {
    while (first != last) {
      this->splice(position, that, first++);
    }
  }

  /**
   * inserts this list into an ostream, with the format [element1, element2, element3, ...].
   * 
   * @param out	ostream object where the list is inserted
   * @param list the list object to insert
   */
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
  class Iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using reference = T&;

    // Default constructor
    Iterator() {}

    // Copy constructor
    Iterator(const Iterator& other) : cur(other.cur) {}

    // Overloaded constructor
    Iterator(Node* cur_node, Node* cur_tail) {
      this->cur = cur_node;
      this->tail = cur_tail;
    }

    // Assignment
    Iterator& operator=(const Iterator& that) {
      this->cur = that.cur;
      this->tail = that.tail;
      return *this;
    }

    // Prefix increment
    Iterator& operator++() {
      this->cur = this->cur->next;
      return *this;
    }

    // Postfix increment
    Iterator operator++(int) {
      Iterator tmp(*this);
      this->operator++();
      return tmp;
    }

    // Prefix decrement
    Iterator& operator--() {
      if (this->cur == nullptr) {
        this->cur = this->tail;
      } else {
        this->cur = this->cur->prev;
      }
      return *this;
    }

    // Postfix decrement
    Iterator operator--(int) {
      Iterator tmp(*this);
      this->operator--();
      return tmp;
    }

    // Inequality
    bool operator!=(Iterator that) const { return !(this->operator==(that)); }

    // Equality
    bool operator==(Iterator that) const { return this->cur == that.cur; }

    // lvalue dereference
    T& operator*() const { return this->cur->data; }

    // referring
    Iterator* operator->() { return this; }

    // Getter for cur
    Node* get_cur() { return this->cur; }

   private:
    Node* cur = nullptr;
    Node* tail = nullptr;
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;
};
}  // namespace cs19

#endif  // CS19_LINKED_LIST_RAW_POINTERS_ITERABLE_H_
