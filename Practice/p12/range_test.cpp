/**
 * @file range_test.cpp
 *
 * Exercising the simple iterable cs19::Range type.
 *
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include "cs19_range.h"

int main() {
  cs19::Range range(10, 20, 2);  // 0 --> 9
  // Iterate and print using begin() and end() manually:
  for (auto it = range.begin(); it != range.end(); ++it)
    std::cout << *it << ", ";
  std::cout << '\n';
  // Iterate and print using range-based for loop:
  for (auto &&el : range) {
    std::cout << el << ", ";
  }
  std::cout << '\n';
  // All the STL algorithms etc. are available, since we have iterators
  std::copy(range.begin(), range.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << '\n' << std::accumulate(range.begin(), range.end(), 0) << '\n';
}


