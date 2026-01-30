#include <iostream>
#include <cstdlib>
#include "Array.hpp"

#define MAX_VAL 750

int main(int, char**) {
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;

    // Additional simple tests
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Additional tests:" << std::endl;
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "!";
    
    std::cout << "Size of strings array: " << strings.size() << std::endl;
    for (unsigned int i = 0; i < strings.size(); i++) {
        std::cout << strings[i] << " ";
    }
    std::cout << std::endl;

    Array<std::string> stringsCopy(strings);
    strings[0] = "Modified";
    std::cout << "Original[0]: " << strings[0] << std::endl;
    std::cout << "Copy[0]: " << stringsCopy[0] << std::endl;
    if (strings[0] == stringsCopy[0]) {
        std::cerr << "Deep copy failed!" << std::endl;
    } else {
        std::cout << "Deep copy successful!" << std::endl;
    }

    return 0;
}
