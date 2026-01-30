#include <iostream>
#include "iter.hpp"

// Test function for non-const int
void printInt(int &i) {
    std::cout << i << " ";
}

// Test function for const int
void printConstInt(int const &i) {
    std::cout << i << " ";
}

// Template function to be instantiated
template <typename T>
void printElement(T &t) {
    std::cout << t << " ";
}

template <typename T>
void increment(T &t) {
    t++;
}

class Awesome {
    public:
        Awesome( void ) : _n( 42 ) { return; }
        int get( void ) const { return this->_n; }
    private:
        int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template< typename T >
void print( T const & x ) { std::cout << x << std::endl; return; }

int main() {
    int array[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(array) / sizeof(int);

    std::cout << "Original array: ";
    iter(array, length, printInt);
    std::cout << std::endl;

    std::cout << "Incrementing array..." << std::endl;
    iter(array, length, increment<int>);

    std::cout << "Modified array: ";
    iter(array, length, printElement<int>);
    std::cout << std::endl;

    // Const array test
    int const constArray[] = {10, 20, 30};
    size_t constLength = sizeof(constArray) / sizeof(int);
    std::cout << "Const array: ";
    iter(constArray, constLength, printConstInt);
    std::cout << std::endl;
    
    // Evaluation sheet test simulation
    int tab[] = { 0, 1, 2, 3, 4 }; 
    Awesome tab2[5];

    iter( tab, 5, print<int> );
    iter( tab2, 5, print<Awesome> );

    return 0;
}
