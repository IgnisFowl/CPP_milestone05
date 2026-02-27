# C++ Module 08 — Templated Containers, Iterators & Algorithms

This module introduces the **C++ Standard Template Library (STL)**: containers, iterators,
and algorithms. The exercises are designed to be solvable without the STL, but the whole
point is to *use* it — correctly and extensively.

---

## Exercise 00 — Easy find (`ex00/`)

### What it does
A single templated function `easyfind(T& container, int value)` that searches for the
first occurrence of `value` inside any container of integers. Throws `std::runtime_error`
if the value is not found.

```cpp
std::vector<int> v = {1, 2, 42, 99};
easyfind(v, 42);   // returns iterator to 42
easyfind(v, 100);  // throws std::runtime_error
```

### Key STL tool used
- **`std::find`** (`<algorithm>`) — generic linear search over any range defined by
  `begin()` / `end()` iterators.

### What you learn
- How to write a **function template** that works with any container type `T`.
- The **iterator pattern**: every STL container exposes `begin()` and `end()`, and
  algorithms operate on those iterators — not on the container directly.
- How `std::find` returns `end()` to signal "not found", mirroring the STL convention.
- Why associative containers (`std::map`, `std::set`) are a special case — their
  elements are keys/values, not plain integers in a sequence, so `std::find` doesn't
  make sense for them in the same way.

---

## Exercise 01 — Span (`ex01/`)

### What it does
A class `Span` that stores up to `N` integers and can compute:
- **`shortestSpan()`** — the smallest difference between any two stored numbers.
- **`longestSpan()`** — the largest difference (max − min).
- **`addRange(begin, end)`** — a template method to bulk-load numbers from any pair
  of iterators (instead of calling `addNumber()` thousands of times).

```cpp
Span sp(5);
sp.addNumber(6); sp.addNumber(3); sp.addNumber(17);
sp.addNumber(9); sp.addNumber(11);
sp.shortestSpan(); // 2  (11 − 9, not 6 − 3)
sp.longestSpan();  // 14 (17 − 3)
```

### Key STL tools used
- **`std::sort`** — to order the numbers so adjacent elements give minimum differences.
- **`std::min_element` / `std::max_element`** — to find the extremes for `longestSpan`.
- **`std::vector::insert(pos, first, last)`** — to add a range of elements in one call.
- **`std::distance`** — to count how many elements a range contains.

### What you learn
- **STL algorithms work on ranges**, not containers — any pair of iterators is enough.
- Why the shortest span is *not* simply `second_lowest − lowest`: you must sort and
  check every adjacent pair to handle cases like `{1, 100, 101}` where the gap between
  100 and 101 (= 1) is smaller than 100 − 1.
- How to write a **member function template** (`addRange`) inside a regular class,
  so the class itself isn't a template but one of its methods is.
- The Orthodox Canonical Form: copy constructor, copy assignment operator, destructor —
  essential whenever a class manages resources (here, a `std::vector`).

---

## Exercise 02 — MutantStack (`ex02/`)

### What it does
`std::stack` is intentionally non-iterable — it only exposes `push`, `pop`, `top`, and
`size`. `MutantStack<T>` inherits from `std::stack<T>` and adds full iterator support
by exposing the protected underlying container `c`.

```cpp
MutantStack<int> ms;
ms.push(5); ms.push(3); ms.push(737);

MutantStack<int>::iterator it = ms.begin();
while (it != ms.end())
    std::cout << *it++ << std::endl;  // 5  3  737 (bottom to top)
```

### Key concept
`std::stack` is a **container adaptor**: it wraps another container (by default
`std::deque`) stored in a protected member called `c`. By inheriting from `std::stack`
and forwarding calls to `c.begin()` / `c.end()`, we expose iterators without
reimplementing the stack logic.

```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
iterator begin() { return this->c.begin(); }
iterator end()   { return this->c.end();   }
```

### What you learn
- **Container adaptors** (`std::stack`, `std::queue`, `std::priority_queue`): they add
  a restricted interface on top of a real container rather than storing data directly.
- **Protected inheritance members**: `std::stack` intentionally exposes `c` as
  `protected` so subclasses can extend it — a deliberate STL design choice.
- **Iterator categories**: `iterator`, `const_iterator`, `reverse_iterator` —
  providing all four makes the class a proper first-class STL citizen.
- That the same algorithm/loop works identically on `MutantStack` and on `std::list`
  once you expose a compatible iterator interface — demonstrating why **generic
  programming** with iterators is so powerful.

---

## General takeaways from Module 08

| Concept | Where it appears |
|---|---|
| Function templates | `easyfind` (ex00) |
| STL algorithms (`<algorithm>`) | `std::find`, `std::sort`, `std::min/max_element` |
| Iterator-based ranges | all three exercises |
| Container adaptors | `std::stack` (ex02) |
| Member function templates | `Span::addRange` (ex01) |
| Orthodox Canonical Form | `Span` (ex01), `MutantStack` (ex02) |
| Exceptions for error signalling | all three exercises |
