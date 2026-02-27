#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
  // --- Subject example with MutantStack ---
  std::cout << "=== MutantStack ===" << std::endl;
  {
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl; // 17

    mstack.pop();

    std::cout << mstack.size() << std::endl; // 1

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;

    while (it != ite) {
      std::cout << *it << std::endl;
      ++it;
    }

    std::stack<int> s(mstack);
    (void)s;
  }

  // --- Same test with std::list ---
  std::cout << "\n=== std::list (same logic) ===" << std::endl;
  {
    std::list<int> mlist;

    mlist.push_back(5);
    mlist.push_back(17);

    std::cout << mlist.back() << std::endl; // 17

    mlist.pop_back();

    std::cout << mlist.size() << std::endl; // 1

    mlist.push_back(3);
    mlist.push_back(5);
    mlist.push_back(737);
    mlist.push_back(0);

    std::list<int>::iterator it = mlist.begin();
    std::list<int>::iterator ite = mlist.end();

    ++it;
    --it;

    while (it != ite) {
      std::cout << *it << std::endl;
      ++it;
    }
  }

  return 0;
}
