/**
 * @file cs19_avl.h
 *
 * @author Jeffrey Bergamini for CS 19, tw // historical trauma
 * jeffrey.bergamini@cabrillo.edu
 * @author Stephanie a L'heureux for CS 19, tw // historical trauma
 * salheureux@cabrillo.edu
 */
#ifndef CS19_AVL_H_
#define CS19_AVL_H_

#include <algorithm>
#include <vector>
#include <memory>

namespace cs19 {

/**
 * An implementation of a set class using an AVL tree. Insertion, search and
 * removal are O(log n).
 * Fully functional, but with memory leaks when removing a set key or destroying
 * a set.
 *
 * @see https://en.wikipedia.org/wiki/AVL_tree
 * @tparam T any type of which instances are mutually comparable using operator<
 */
template <typename T>
class AVLset {
  class Node;  // forward-declared node type

 public:
  // adds a key to the set
  void insert(T key) { this->root_ = insert(this->root_, key); }
  // removes a key from the set
  void erase(T key) { this->root_ = erase(this->root_, key); }
  // membership test
  bool contains(T key) {
    this->comparison_count_ = 0;  // prepare to count key comparisons

    return this->search(this->root_, key) != nullptr;
  }
  // size of the set
  std::size_t size() const { return this->size_; }
  // result of an inorder traversal (should be the set keys in ascending order)
  std::vector<T> inorder() {
    std::vector<T> results;
    inorder(this->root_, &results);
    return results;
  }
  // for verifying how many comparisons a membership test operation requires
  std::size_t comparison_count() const { return this->comparison_count_; }

 private:
  std::shared_ptr<Node> root_ = nullptr;  // the root of the tree
  std::size_t size_ = 0;                  // the size of the set
  std::size_t comparison_count_;          // used in search()
  struct Node {
    Node(T key) : key(key) {
      // nothing to do here
    }
    T key;           // an actual key in the set
    int height = 1;  // the height of this node in the tree (used in
                     // rebalancing/rotating)
    std::shared_ptr<Node> left = nullptr;   // the left child
    std::shared_ptr<Node> right = nullptr;  // the right child
  };
  // simple helper returning the height of the tree rooted at head
  int height(std::shared_ptr<Node> head) { return head ? head->height : 0; }
  // used in rebalancing
  std::shared_ptr<Node> rotate_right(std::shared_ptr<Node> head) {
    std::shared_ptr<Node> new_head = head->left;
    head->left = new_head->right;
    new_head->right = head;
    head->height = 1 + std::max(height(head->left), height(head->right));
    new_head->height =
        1 + std::max(height(new_head->left), height(new_head->right));
    return new_head;
  }
  // used in rebalancing
  std::shared_ptr<Node> rotate_left(std::shared_ptr<Node> head) {
    std::shared_ptr new_head = head->right;
    head->right = new_head->left;
    new_head->left = head;
    head->height = 1 + std::max(height(head->left), height(head->right));
    new_head->height =
        1 + std::max(height(new_head->left), height(new_head->right));
    return new_head;
  }
  // recursively assembles a vector of keys via inorder traversal
  void inorder(std::shared_ptr<Node> head, std::vector<T>* results) {
    if (!head) return;
    inorder(head->left, results);
    results->push_back(head->key);
    inorder(head->right, results);
  }
  // recursive insertion
  std::shared_ptr<Node> insert(std::shared_ptr<Node> head, T new_key) {
    if (!head) {
      ++this->size_;
      return std::make_shared<Node>(new_key);
      // return new Node(new_key); // new used here
    }
    if (head->key == new_key) return head;
    if (new_key < head->key)
      head->left = insert(head->left, new_key);
    else if (new_key > head->key)
      head->right = insert(head->right, new_key);
    head->height = 1 + std::max(height(head->left), height(head->right));
    int bal = height(head->left) - height(head->right);
    if (bal > 1) {
      if (new_key < head->left->key) {
        return rotate_right(head);
      } else {
        head->left = rotate_left(head->left);
        return rotate_right(head);
      }
    } else if (bal < -1) {
      if (new_key > head->right->key) {
        return rotate_left(head);
      } else {
        head->right = rotate_right(head->right);
        return rotate_left(head);
      }
    }
    return head;
  }
  // recursive deletion
  std::shared_ptr<Node> erase(std::shared_ptr<Node> head, T x) {
    if (!head) return nullptr;
    if (x < head->key) {
      head->left = erase(head->left, x);
    } else if (x > head->key) {
      head->right = erase(head->right, x);
    } else {
      std::weak_ptr<Node> r = std::weak_ptr<Node>(head->right);  // change??
      if (!head->right) {
        head = head->left;
        --this->size_;
      } else if (!head->left) {
        head = r.lock();
        --this->size_;
      } else {
        while (r.lock()->left) r = std::weak_ptr<Node>(r.lock()->left);
        head->key = r.lock()->key;
        head->right = erase(head->right, r.lock()->key);
      }
    }
    if (!head) return nullptr;
    head->height = 1 + std::max(height(head->left), height(head->right));
    int bal = height(head->left) - height(head->right);
    if (bal > 1) {
      if (height(head->left) >= height(head->right)) {
        return rotate_right(head);
      } else {
        head->left = rotate_left(head->left);
        return rotate_right(head);
      }
    } else if (bal < -1) {
      if (height(head->right) >= height(head->left)) {
        return rotate_left(head);
      } else {
        head->right = rotate_right(head->right);
        return rotate_left(head);
      }
    }
    return head;
  }
  // recursive membership test
  std::shared_ptr<Node> search(std::shared_ptr<Node> head, T key) {
    if (!head) return nullptr;
    ++this->comparison_count_;  // make sure we count key comparisons
    if (key == head->key) return head;
    if (key < head->key) return search(head->left, key);
    return search(head->right, key);
  }
};

}  // namespace cs19

#endif