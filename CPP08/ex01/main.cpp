#include "Span.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main() {
  // --- Subject example ---
  std::cout << "=== Subject example ===" << std::endl;
  {
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl; // expected: 2
    std::cout << sp.longestSpan() << std::endl;  // expected: 14
  }

  // --- Exception: adding to a full Span ---
  std::cout << "\n=== Adding to full Span ===" << std::endl;
  {
    Span sp(2);
    sp.addNumber(1);
    sp.addNumber(2);
    try {
      sp.addNumber(3);
    } catch (std::exception &e) {
      std::cout << "Expected exception: " << e.what() << std::endl;
    }
  }

  // --- Exception: span on 0 or 1 element ---
  std::cout << "\n=== Span on empty / single element ===" << std::endl;
  {
    Span sp(5);
    try {
      sp.shortestSpan();
    } catch (std::exception &e) {
      std::cout << "Expected exception (empty): " << e.what() << std::endl;
    }
    sp.addNumber(42);
    try {
      sp.longestSpan();
    } catch (std::exception &e) {
      std::cout << "Expected exception (1 element): " << e.what() << std::endl;
    }
  }

  // --- Bulk addRange with 10,000 numbers ---
  std::cout << "\n=== addRange with 10,000 numbers ===" << std::endl;
  {
    const unsigned int N = 10000;
    Span sp(N);

    std::vector<int> src;
    src.reserve(N);
    std::srand(42);
    for (unsigned int i = 0; i < N; ++i)
      src.push_back(std::rand() % 100000);

    sp.addRange(src.begin(), src.end());
    std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
    std::cout << "longestSpan:  " << sp.longestSpan() << std::endl;
  }

  // --- addRange overflow check ---
  std::cout << "\n=== addRange overflow check ===" << std::endl;
  {
    Span sp(3);
    sp.addNumber(1);
    std::vector<int> extra;
    extra.push_back(2);
    extra.push_back(3);
    extra.push_back(4); // one too many
    try {
      sp.addRange(extra.begin(), extra.end());
    } catch (std::exception &e) {
      std::cout << "Expected exception: " << e.what() << std::endl;
    }
  }

  return 0;
}
