#ifndef ITER_HPP
# define ITER_HPP

# include <cstddef> // for size_t

// Template for non-const array and function taking non-const reference
template <typename T>
void iter(T *array, size_t length, void (*func)(T &)) {
    for (size_t i = 0; i < length; i++) {
        func(array[i]);
    }
}

// Template for const array and function taking const reference
template <typename T>
void iter(T const *array, size_t length, void (*func)(T const &)) {
    for (size_t i = 0; i < length; i++) {
        func(array[i]);
    }
}

// Should I also support a functor? The subject says "The third is a function".
// But usually function templates are implemented as:
// template <typename T, typename Func>
// void iter(T *array, size_t length, Func func)
// However, the requirement about "instantiated function template" suggests we are passing a function pointer.
// And "accept its argument by const reference or non-const reference" suggests strict type matching might be expected or we need to handle it.
// The two overloads above seem to safery cover "const T*" and "T*" arrays interacting with "void (*)(const T&)" and "void (*)(T&)".

#endif
