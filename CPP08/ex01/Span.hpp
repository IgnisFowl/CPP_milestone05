#ifndef SPAN_HPP
#define SPAN_HPP

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

class Span {
public:
  Span(unsigned int n);
  Span(const Span &other);
  Span &operator=(const Span &other);
  ~Span();

  void addNumber(int n);

  template <typename InputIterator>
  void addRange(InputIterator begin, InputIterator end) {
    unsigned int count = static_cast<unsigned int>(std::distance(begin, end));
    if (_numbers.size() + count > _maxSize)
      throw std::runtime_error("Span: not enough capacity to add range");
    _numbers.insert(_numbers.end(), begin, end);
  }

  int shortestSpan() const;
  int longestSpan() const;

private:
  unsigned int _maxSize;
  std::vector<int> _numbers;
};

#endif
