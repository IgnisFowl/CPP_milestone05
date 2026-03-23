# C++ Module 09 — STL (Standard Template Library)

## Overview

This module introduces the **STL (Standard Template Library)** in C++98. The challenge is not just to use containers, but to use each container **only once** across the three exercises — forcing you to think about which container is the right tool for each problem.

---

## Exercise 00 — Bitcoin Exchange (`btc`)

### What it does
Reads a CSV database of historical Bitcoin prices (`data.csv`) and an input file of `date | value` pairs. For each line, it multiplies the value by the exchange rate at the closest date ≤ the requested date, and prints the result.

### How it works
- The database is loaded into a **`std::map<std::string, float>`**, mapping ISO date strings (`YYYY-MM-DD`) to exchange rates.
- For each input line, the date and value are parsed and validated.
- `std::map::lower_bound(date)` finds the first key ≥ the requested date. If it's not an exact match, we step back one position (`--it`) to get the closest earlier date.
- Errors (bad date, negative value, value > 1000, missing separator) are printed and execution continues — the program never aborts mid-file.

### Why `std::map`?
ISO date strings in `YYYY-MM-DD` format sort **lexicographically = chronologically**, so a sorted `map` gives us the "closest earlier date" lookup for free via `lower_bound`, in O(log n) time.

### What I learned
- How to use associative containers (`std::map`) for efficient key-based lookups
- Using `lower_bound` / `upper_bound` for range queries
- Robust input parsing and error handling without crashing

```bash
cd ex00 && make
./btc input.txt
```

---

## Exercise 01 — Reverse Polish Notation (`RPN`)

### What it does
Takes a mathematical expression in Reverse Polish Notation (postfix) as a command-line argument and evaluates it, printing the integer result.

Examples:
```
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"   # → 42
./RPN "7 7 * 7 -"                      # → 42
./RPN "(1 + 1)"                        # → Error
```

### How it works
Tokens are read left to right:
- A **digit (0–9)** is pushed onto the stack.
- An **operator (`+ - * /`)** pops the top two values, applies the operation, and pushes the result.
- Any other token (parentheses, multi-character strings) triggers an error.
- At the end, the stack must contain exactly one value — the result.

### Why `std::stack`?
RPN evaluation is literally the textbook use case for a stack. "Last in, first out" maps directly to the way operands are consumed by operators.

### What I learned
- How stacks model expression evaluation
- Tokenizing and parsing input with `std::istringstream`
- Error handling in expression evaluation (stack underflow, invalid tokens, division by zero)

```bash
cd ex01 && make
./RPN "3 4 + 2 *"   # → 14
```

---

## Exercise 02 — PmergeMe (`PmergeMe`)

### What it does
Sorts a sequence of positive integers using the **Ford-Johnson merge-insertion sort** algorithm, implemented independently for two containers. It displays the sequence before and after sorting, plus the time taken by each container.

```
./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 12 us
Time to process a range of 5 elements with std::deque  :  9 us
```

### How it works — Ford-Johnson algorithm

Ford-Johnson (merge-insertion sort) is designed to **minimize the number of comparisons** needed to sort n elements. The steps are:

1. **Pair up** adjacent elements; within each pair, place the larger element first.
2. **Recursively sort** the sequence of "larger" elements — this builds the *main chain*.
3. The first "smaller" element is guaranteed to be ≤ the first element of the sorted chain, so it's inserted at the front for free.
4. The remaining "smaller" (pending) elements are inserted into the chain via **binary search**, in an order determined by the **Jacobsthal sequence** to minimize worst-case comparisons.
5. Any leftover element (when n is odd) is also inserted via binary search.

#### Jacobsthal sequence
Defined as: J(0)=0, J(1)=1, J(n) = J(n-1) + 2·J(n-2)  
→ 0, 1, 1, 3, 5, 11, 21, 43, …

Inserting pending elements in Jacobsthal order ensures each binary search operates on a region whose size is ≤ 2^k − 1 for some k, meaning we never waste a comparison — this is what makes Ford-Johnson optimal.

#### Binary search
When inserting a pending element, we know it is ≤ its paired "large" element (already in the chain). So we only binary-search up to that partner's position, keeping the search range tight.

### Why `std::vector` and `std::deque`?
Both support **random access** (needed for binary search by index) and **arbitrary insertion** (`insert()`). They have different memory layouts: `vector` uses a single contiguous block (better cache locality), while `deque` uses chunked blocks (better for frequent front insertions). This makes the comparison interesting and educational.

### What I learned
- The Ford-Johnson algorithm and why comparison-minimizing algorithms matter
- The Jacobsthal sequence as a tool for optimal insertion ordering
- Measuring performance with `gettimeofday`
- That two containers with similar interfaces can have meaningfully different runtime characteristics

```bash
cd ex02 && make
./PmergeMe 3 5 9 7 4
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")
```

---

## Container Usage (Module Rule: No Repeats)

| Exercise | Container | Reason |
|---|---|---|
| ex00 | `std::map` | Sorted key-value store; `lower_bound` for date lookup |
| ex01 | `std::stack` | LIFO — perfect for RPN evaluation |
| ex02 | `std::vector` + `std::deque` | Random access + insertion; two required by subject |

---

## Compilation

Each exercise has its own `Makefile`:
```bash
# In each ex0X/ directory:
make        # build
make clean  # remove .o files
make fclean # remove .o files + binary
make re     # full rebuild
```

Compiled with: `c++ -Wall -Wextra -Werror -std=c++98`
