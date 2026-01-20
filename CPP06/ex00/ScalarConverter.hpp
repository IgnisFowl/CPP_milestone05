#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <climits>
#include <cfloat>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <iomanip>

class ScalarConverter {
public:
    static void convert(std::string const& literal);

private:
    ScalarConverter();
    ScalarConverter(ScalarConverter const& other);
    ScalarConverter & operator=(ScalarConverter const& other);
    ~ScalarConverter();
};

#endif
