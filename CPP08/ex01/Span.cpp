#include "Span.hpp"
#include <algorithm>
#include <climits>
#include <stdexcept>

Span::Span(unsigned int n) : _maxSize(n) {}

Span::Span(const Span &other)
    : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other) {
  if (this != &other) {
    _maxSize = other._maxSize;
    _numbers = other._numbers;
  }
  return *this;
}

Span::~Span() {}

void Span::addNumber(int n) {
  if (_numbers.size() >= _maxSize)
    throw std::runtime_error("Span: already full, cannot add more numbers");
  _numbers.push_back(n);
}

int Span::shortestSpan() const {
  if (_numbers.size() <= 1)
    throw std::runtime_error("Span: not enough elements to compute a span");

  std::vector<int> sorted(_numbers);
  std::sort(sorted.begin(), sorted.end());

  int shortest = INT_MAX;
  for (std::size_t i = 1; i < sorted.size(); ++i) {
    int diff = sorted[i] - sorted[i - 1];
    if (diff < shortest)
      shortest = diff;
  }
  return shortest;
}

int Span::longestSpan() const {
  if (_numbers.size() <= 1)
    throw std::runtime_error("Span: not enough elements to compute a span");

  int minVal = *std::min_element(_numbers.begin(), _numbers.end());
  int maxVal = *std::max_element(_numbers.begin(), _numbers.end());
  return maxVal - minVal;
}
