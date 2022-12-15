#ifndef CS19_SEARCH_SORT_H_
#define CS19_SEARCH_SORT_H_

/**
 * Namespace cs19 contains functions for our search and sort assignment.
 *
 * @author Stephanie L'Heureux for CS 19, saheureux@jeff.cis.cabrillo.edu
 */
namespace cs19 {

/**
 * Value 'a' is swapped with 'b'. Models std::swap()
 *
 * @tparam Value a value type that supports `operator=`
 *
 * @param a Value to be swapped with 'b'
 * @param b Value to be swapped with 'a'
 */
template <typename Value>
void swap(Value& a, Value& b) {
  Value temp = a;
  a = b;
  b = temp;
}

/**
 * Returns an iterator moved on position forward
 *
 * @tparam Iterator a position iterator that supports the [standard input iterator
 * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
 *
 * @param irt An iterator
 */
template <typename Iterator>
Iterator forward(Iterator itr) {
  return ++itr;
}

/**
 * Returns an iterator to the first element in the range `[first,last)` that compares equal to
 * `val`. If no such element is found, the function returns `last`.
 *
 * @tparam Iterator a position iterator that supports the [standard input iterator
 * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
 * @tparam Value a value type that supports `operator==`
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 * @param val the value for which to search
 * @return an iterator to the first element in the range that compares equal to `val`. If no
 * elements match, the function returns `last`.
 */
template <typename Iterator, typename Value>
Iterator linear_search(Iterator first, Iterator last, const Value &val) {
  for (; first != last; first++) {
    if (*first == val) return first;
  }
  return last;
}

/**
 * Performs an index-based linear search on an indexable object for a given value.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must be of template type `Value`.
 * @tparam Value a value type that supports `operator==`
 *
 * @param haystack the object to search
 * @param needle the value for which to search
 * @return the first index found via linear search at which `haystack` contains `needle`, or `-1` if
 * `haystack` does not contain `needle`
 */
template <typename IndexedContainer, typename Value>
int linear_search(const IndexedContainer &haystack, const Value &needle) {
  unsigned size = haystack.size();
  for (unsigned i = 0; i < size; i++) {
    if (haystack[i] == needle) return i;
  }
  return -1;
}

/**
 * Performs an index-based binary search on an indexable object for a given value.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must be of template type `Value`.
 * @tparam Value a value type that supports `operator==` and `operator<`
 *
 * @param haystack the object to search
 * @param needle the value for which to search
 * @return the first index found via binary search at which `haystack` contains `needle`, or `-1` if
 * `haystack` does not contain `needle`
 */
template <typename IndexedContainer, typename Value>
int binary_search(const IndexedContainer &haystack, const Value &needle) {
  int low = 0;
  int high = haystack.size() -1;
  int mid;

  while (low <= high) {
    mid = (low + high) / 2;
    if (haystack[mid] == needle) {
      return mid;
    } else if (haystack[mid] > needle) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

/**
 * Performs an index-based bubble sort on any indexable container object.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must support `operator<` and `operator=`.
 *
 * @param values the object to sort
 */
template <typename IndexedContainer>
void bubble_sort(IndexedContainer &values) {
  bool swapped;
  unsigned size = values.size();
  do {
    swapped = false;
    for (unsigned i = 0; i < size - 1; i++) {
      if (values[i] > values[i + 1]) {
        swap(values[i], values[i + 1]);
        swapped = true;
      }
    }
  } while (swapped);
}

/**
 * Sorts the elements in the range `[first,last)` into ascending order, using the bubble-sort
 * algorithm. The elements are compared using `operator<`.
 *
 * @tparam Iterator a position iterator that supports the [standard bidirectional iterator
 * operations](http://www.cplusplus.com/reference/iterator/BidirectionalIterator/)
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 */
template <typename Iterator>
void bubble_sort(Iterator first, Iterator last) {
  bool swapped;
  last--;
  do {
    swapped = false;
    for (auto a = first, b = forward(a); a != last; b++, a++) {
      if (*a > *b) {
        swap(*a, *b);
        swapped = true;
      }
    }
  } while (swapped);
}

/**
 * Performs an index-based selection sort on an indexable object.
 *
 * @tparam IndexedContainer must support `operator[]` and `size()`, e.g. `std::vector`. Container
 * elements must support `operator<` and `operator=`.
 *
 * @param values the object to sort
 */
template <typename IndexedContainer>
void selection_sort(IndexedContainer &values) {
  int lowest;
  unsigned size = values.size();

  for (unsigned i = 0; i < size - 1; i++) {
    lowest = i;
    for (unsigned j = i + 1; j < size; j++) {
      if (values[j] < values[lowest]) {
        lowest = j;
      }
    }
    swap(values[i], values[lowest]);
  }
}

/**
 * Sorts the elements in the range `[first,last)` into ascending order, using the selection-sort
 * algorithm.
 *
 * @tparam Iterator a position iterator that supports the [standard input iterator
 * operations](http://www.cplusplus.com/reference/iterator/InputIterator/)
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 */
template <typename Iterator>
void selection_sort(Iterator first, Iterator last) {
  Iterator lowest;

  for (auto i = first; i != last; i++) {
    lowest = i;
    for (auto j = forward(i); j != last; j++) {
      if (*j < *lowest) {
        lowest = j;
      }
    }
    swap(*i, *lowest);
  }
}

}  // namespace cs19

#endif  // CS19_SEARCH_SORT_H_