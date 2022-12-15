/**
 * Some assertion tests demonstrating the capabilities of an AVL-tree-based set.
 * @author Jeffrey Bergamini for CS 19, tw // historical trauma jeffrey.bergamini@cabrillo.edu
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>
// #include "cs19_avl.h"  // using the provided version
#include "cs19_avl_smart_pointers.h"  // using your modified version

int main() {
  std::set<std::string> stl_set;
  cs19::AVLset<std::string> avl_set;
  // add all whitespace-delimited tokens to the sets and verify functionality
  for (std::string token; std::cin >> token;) {
    if (!stl_set.contains(token))
      assert(!avl_set.contains(token));
    assert(stl_set.size() == avl_set.size());
    stl_set.insert(token);
    avl_set.insert(token);
    assert(stl_set.size() == avl_set.size());
    assert(avl_set.contains(token));
    assert(avl_set.comparison_count() <= std::max(1.0, 2 * std::log2(avl_set.size())));
    assert(std::vector(stl_set.begin(), stl_set.end()) == avl_set.inorder());
  }
  // remove all values in random order
  std::vector all_values(stl_set.begin(), stl_set.end());
  std::random_device rd;
  std::mt19937 prng(rd());
  std::shuffle(all_values.begin(), all_values.end(), prng);
  for (auto &&key : all_values) {
    stl_set.erase(key);
    avl_set.erase(key);
    assert(stl_set.size() == avl_set.size());
    assert(!avl_set.contains(key));
    assert(avl_set.comparison_count() <= std::max(1.0, 2 * std::log2(avl_set.size())));
    assert(std::vector(stl_set.begin(), stl_set.end()) == avl_set.inorder());
  }
}
