#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(Array const &src) : _array(NULL), _size(0) {
    *this = src;
}

template <typename T>
Array<T>::~Array() {
    delete [] _array;
}

template <typename T>
Array<T> & Array<T>::operator=(Array const &rhs) {
    if (this != &rhs) {
        delete [] _array;
        _size = rhs.size();
        _array = new T[_size]();
        for (unsigned int i = 0; i < _size; i++) {
            _array[i] = rhs._array[i];
        }
    }
    return *this;
}

template <typename T>
T & Array<T>::operator[](unsigned int i) {
    if (i >= _size) {
        throw OutOfBoundsException();
    }
    return _array[i];
}

template <typename T>
T const & Array<T>::operator[](unsigned int i) const {
    if (i >= _size) {
        throw OutOfBoundsException();
    }
    return _array[i];
}

template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}

template <typename T>
const char* Array<T>::OutOfBoundsException::what() const throw() {
    return "Index out of bounds";
}

#endif
