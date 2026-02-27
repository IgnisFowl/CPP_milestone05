#include "easyfind.hpp"
#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main() {
  // --- Test with std::vector ---
  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(42);
  vec.push_back(7);
  vec.push_back(99);
  vec.push_back(-5);

  std::cout << "=== std::vector ===" << std::endl;
  try {
    std::vector<int>::iterator it = easyfind(vec, 42);
    std::cout << "Found 42 at position " << std::distance(vec.begin(), it)
              << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  try {
    easyfind(vec, 100);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }

  // --- Test with std::list ---
  std::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_back(4);
  lst.push_back(5);

  std::cout << "\n=== std::list ===" << std::endl;
  try {
    std::list<int>::iterator it = easyfind(lst, 3);
    std::cout << "Found 3 in list" << std::endl;
    (void)it;
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  try {
    easyfind(lst, 999);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }

  // --- Test with std::deque ---
  std::deque<int> dq;
  dq.push_back(100);
  dq.push_back(200);
  dq.push_back(300);

  std::cout << "\n=== std::deque ===" << std::endl;
  try {
    std::deque<int>::iterator it = easyfind(dq, 200);
    std::cout << "Found 200 at position " << std::distance(dq.begin(), it)
              << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  try {
    easyfind(dq, 0);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }

  return 0;
}
