/**
 * @file cs19_range.h
 *
 * An iterable type representing a range of integers, similar to Python's built-in range
 * (ascending values and step by 1 only, to keep it simple).
 *
 * @author Jeffrey Bergamini and Stephanie L'Heureux
 */

#ifndef CS19_RANGE_H_
#define CS19_RANGE_H_

#include <iostream>

namespace cs19 {

class Range {
  struct Iterator;  // forward-declared iterator member type

 public:
  // Constructor for numeric ranges, starting at 0 and stepping by 1
  Range(int stop) : start(0), stop(stop), step(1) {
  }
  // Constructor for numeric ranges, stepping by 1
  Range(int start, int stop) : start(start), stop(stop), step(1)  {
  }

  Range(int start, int stop, int step) : start(start), stop(stop), step(step) {
  }
  // Returns an iterator pointing to the first element in the range
  Iterator begin() {
    return {this, this->start, step};
  }
  // Returns an iterator referring to the past-the-end element in the range
  Iterator end() {
    return {this, this->stop, step};
  }

 private:
  int start;
  int stop;
  int step;
  // Iterator kept as a struct for brevity; should probably be a class with encapsulation
  struct Iterator {
    // Type aliases that will allow this iterator to work seamlessly with STL etc.
    // See: https://en.cppreference.com/w/cpp/language/type_alias
    // See: https://internalpointers.com/post/writing-custom-iterators-modern-cpp
    // Think of these as tags/configurations:
    using iterator_category = std::input_iterator_tag;
    using value_type = int;       // "dereferencing" an Iterator yields int
    using difference_type = int;  // "distances" between Iterators are int
    using pointer = int*;         // A Iterator* should behave as a int*
    using reference = int&;       // A Iterator& should behave as a int&

    Range* range;  // associate range
    int current;   // current position in range
    int step;

    // prefix increment
    Iterator& operator++() {
      this->current += this->step;
      return *this;
    }
    // postfix increment
    Iterator operator++(int) {
      Iterator tmp(*this);
      this->operator++();
      return tmp;
    }
    // equality
    bool operator==(Iterator that) const {
      return this->range == that.range && this->current == that.current;
    }
    // inequality
    bool operator!=(Iterator that) const {
      return !(*this == that);
    }
    // rvalue dereference
    int operator*() {
      return this->current;
    }
  };
};

}  // namespace cs19

#endif  // CS19_RANGE_H_


