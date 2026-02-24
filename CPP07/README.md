# C++ Module 07 — Templates

This module introduces **C++ templates**, one of the most powerful features of the language. Templates allow you to write code that works with any type, without sacrificing type safety or performance. The compiler generates the concrete versions at compile time.

---

## Exercise 00 — `whatever.hpp`

**Files:** `ex00/whatever.hpp`, `ex00/main.cpp`

### What it does

Implements three generic utility functions as **function templates**:

```cpp
template <typename T> void        swap(T &a, T &b);
template <typename T> T const &   min(T const &a, T const &b);
template <typename T> T const &   max(T const &a, T const &b);
```

These work on any type `T` that supports assignment (`=`) and comparison operators (`<`, `>`).

### What you were supposed to learn

- **Syntax of function templates** — `template <typename T>` before a function declaration.
- **Type deduction** — the compiler figures out `T` from the arguments you pass; you don't need to write `swap<int>(a, b)`, just `swap(a, b)`.
- **Returning by `const` reference** — `min` and `max` return a reference to one of their arguments, avoiding unnecessary copies, while `const` ensures the caller cannot accidentally modify the original through the returned reference.
- **Why templates beat macros** — a `#define swap(a, b)` macro would be type-unsafe and side-effect-prone; a template is fully type-checked by the compiler.
- **Namespace qualification `::swap`** — calling `::swap` instead of `swap` avoids ambiguity with `std::swap`, which is a good habit when you define names that exist in `std`.

---

## Exercise 01 — `iter`

**Files:** `ex01/iter.hpp`, `ex01/main.cpp`

### What it does

Implements a generic `iter` function that applies a callable to every element of an array:

```cpp
template <typename T, typename Func>
void iter(T *array, size_t const length, Func func);
```

Example usage:
```cpp
int tab[] = {1, 2, 3};
iter(tab, 3, print<int>);       // prints each element
iter(tab, 3, increment<int>);   // increments each element

int const ctab[] = {10, 20, 30};
iter(ctab, 3, print<int>);      // works on const arrays too
```

### What you were supposed to learn

- **Multiple template parameters** — `T` for the element type and `Func` for the callable type, allowing total flexibility.
- **Why `Func` as a template parameter is better than a raw function pointer** — `void (*func)(T&)` is rigid: it won't accept a function that takes `const T&`. Making `Func` a template parameter lets the compiler match any compatible callable without you writing overloads.
- **How `const` propagates through templates** — when you pass a `const int*` array, `T` is deduced as `const int`, so `array[i]` naturally yields a `const int&`. No special overload needed.
- **Passing instantiated function templates** — `print<int>` is a **concrete function** produced from a function template. The subject specifically tests that your `iter` accepts these, which it does because `Func` is deduced from whatever you pass.
- **The difference between a function template and a template function** — `print` is a function template (the blueprint); `print<int>` is the instantiation (the concrete function).

---

## Exercise 02 — `Array`

**Files:** `ex02/Array.hpp`, `ex02/Array.tpp`, `ex02/main.cpp`

### What it does

Implements a generic dynamic array as a **class template**:

```cpp
template <typename T>
class Array {
    // ...
};
```

Features:
| Feature | Detail |
|---|---|
| Default constructor | Creates an empty array (`size = 0`) |
| Size constructor | `Array<T>(n)` — allocates `n` value-initialized elements |
| Copy constructor | Deep copy — independent from the original |
| Assignment operator | Deep copy with self-assignment guard |
| `operator[]` (non-const) | Read/write access, throws on out-of-bounds |
| `operator[]` (const) | Read-only access on `const` instances, throws on out-of-bounds |
| `size()` | Returns the number of elements |
| `OutOfBoundsException` | Nested class inheriting `std::exception` |

### What you were supposed to learn

- **Class templates** — `template <typename T>` before a class lets the whole class be generic. Each member function must also carry `template <typename T>` when defined outside the class.
- **Splitting declaration and definition** — `.hpp` files cannot contain template definitions in a `.cpp` file (instantiation happens at compile time, so the definition must be visible where it's used). The convention is to put definitions in a `.tpp` file, included at the bottom of the `.hpp`.
- **The Orthodox Canonical Form for templates** — default constructor, copy constructor, copy assignment operator, destructor. All four must handle memory correctly.
- **Deep vs. shallow copy** — the copy constructor and `operator=` allocate a new array and copy element-by-element, so modifying one instance doesn't affect the other.
- **`operator[]` const overloading** — providing both a `T&` and a `T const&` version allows the same syntax on both const and non-const instances, while enforcing read-only access on const ones at compile time.
- **Value initialization with `new T[n]()`** — the `()` at the end zero-initializes built-in types and default-constructs objects, a subtle but important detail.
- **Nested exception classes** — `OutOfBoundsException` lives inside `Array<T>` and inherits `std::exception`, so it can be caught with `catch (std::exception& e)`.
- **`unsigned int` index and negative indices** — passing `-1` as an `unsigned int` wraps around to a very large number, which is `>= _size` and correctly triggers the bounds check.
