#include "cs19_linked_list_raw_pointers.h"
#include <iostream>
#include <string>
#include <list>

template<typename T> 
void print(const std::list<T>& list) {
  unsigned count = 0;
  std::cout << "[";
  for (const auto& token : list) {
    std::cout << token;
    if (count != list.size() - 1) {
      std::cout << ", ";
    }
    count++;
  }
  std::cout << "]\n\n";
}

int main() {
  std::list<char> list_list = {'o'};
  std::list<char> list_list_1 = {'h'};
  cs19::LinkedList<char> test_list = {'o'};
  cs19::LinkedList<char> test_list_1 = {'h'};

  std::cout << std::boolalpha;

  std::cout << "PRINT TEST\n";
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);
  
  std::cout << "UNIQUE() TEST\n";
  test_list.unique();
  list_list.unique();
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "REVERSE() TEST\n";
  test_list.reverse();
  list_list.reverse();
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "REMOVE() TEST\n";
  test_list.remove('l');
  list_list.remove('l');
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "SIZE() TEST\n";
  std::cout << "cs19:list: " << test_list.size() << std::endl;
  std::cout << "std::list: " << list_list.size() << std::endl << std::endl;

  std::cout << "EMPTY() TEST\n";
  std::cout << "cs19:list: " << test_list.empty() << std::endl;
  std::cout << "std::list: " << list_list.empty() << std::endl << std::endl;

  std::cout << "FRONT() TEST\n";
  std::cout << "cs19:list: " << test_list.front() << std::endl;
  std::cout << "std::list: " << list_list.front() << std::endl << std::endl;

  std::cout << "BACK() TEST\n";
  std::cout << "cs19:list: " << test_list.back() << std::endl;
  std::cout << "std::list: " << list_list.back() << std::endl << std::endl;

  std::cout << "PUSH_BACK() TEST\n";
  test_list.push_back('!'); 
  list_list.push_back('!');
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "PUSH_FRONT() TEST\n";
  test_list.push_front('>');
  list_list.push_front('>');
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "CLEAR() TEST\n";
  test_list.clear();
  list_list.clear();
  std::cout << "cs19:list (should be true): " << test_list.empty() << std::endl;
  std::cout << "std::list (should be true): " << list_list.empty() << std::endl << std::endl;

  std::cout << "POP_BACK() TEST\n";
  test_list.push_front('*');
  list_list.push_front('*');
  test_list.pop_back();
  list_list.pop_back();
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "POP_FRONT() TEST\n";
  test_list.push_front('*');
  list_list.push_front('*');
  test_list.pop_front();
  list_list.pop_front();
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "RESIZE() TEST 1\n";
  test_list.resize(3);
  list_list.resize(3);
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "RESIZE() TEST 2\n";
  test_list.resize(7, 'o');
  list_list.resize(7, 'o');
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "= TEST 1\n";
  test_list = {'H', 'i'};
  list_list = {'H', 'i'};
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "= TEST 2\n";
  test_list = test_list_1;
  list_list = list_list_1;
  std::cout << "cs19:list: " << test_list << '\n';
  std::cout << "std::list: ";
  print(list_list);

  std::cout << "== TEST\n";
  if (test_list_1 == test_list) {
    std::cout << "cs19:list: TRUE" << std::endl;
  } else {
    std::cout << "cs19:list: FALSE" << std::endl;
  }
  if (list_list == list_list_1) {
    std::cout << "cs19:list: TRUE" << std::endl << std::endl;
  } else {
    std::cout << "cs19:list: FALSE" << std::endl << std::endl;
  }

  std::cout << "!= TEST\n";
  if (test_list != test_list_1) {
    std::cout << "cs19:list: TRUE" << std::endl;
  } else {
    std::cout << "cs19:list: FALSE" << std::endl;
  }
  if (list_list != list_list_1) {
    std::cout << "cs19:list: TRUE" << std::endl << std::endl;
  } else {
    std::cout << "cs19:list: FALSE" << std::endl << std::endl;
  }

  return 0;
}




  //   void pop_front() {
  //   if (this->size_ == 0) {
  //     throw std::domain_error("List is empty");
  //   }
  //   if (this->size_ == 1) {
  //     Node* old_head = this->head_;
  //     this->head_ = this->head_->next;
  //     --this->size_;
  //     delete old_head;
  //   } else {
  //     Node* old_head = this->head_;
  //     this->head_ = this->head_->next;
  //     this->head_->prev = nullptr;
  //     --this->size_;
  //     delete old_head;
  //   }
  // }
