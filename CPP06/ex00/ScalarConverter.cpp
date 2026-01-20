#include "ScalarConverter.hpp"
#include <climits>
#include <cfloat>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter const & other) { (void)other; }
ScalarConverter & ScalarConverter::operator=(ScalarConverter const & other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isChar(const std::string& str) {
    return str.length() == 1 && !std::isdigit(str[0]) && std::isprint(str[0]);
}

static bool isInt(const std::string& str) {
    char* end;
    long val = std::strtol(str.c_str(), &end, 10);
    if (*end != '\0')
        return false;
    return val >= INT_MIN && val <= INT_MAX;
}

static bool isFloat(const std::string& str) {
    if (str == "-inff" || str == "+inff" || str == "nanf")
        return true;
    if (str.empty() || str[str.length() - 1] != 'f')
        return false;
    char* end;
    std::strtof(str.c_str(), &end);
    return *end == 'f' && *(end + 1) == '\0';
}

static bool isDouble(const std::string& str) {
    if (str == "-inf" || str == "+inf" || str == "nan")
        return true;
    if (str.empty())
        return false;
    char* end;
    std::strtod(str.c_str(), &end);
    return *end == '\0';
}

void ScalarConverter::convert(std::string const & literal) {
    char   c = 0;
    int    i = 0;
    float  f = 0.0f;
    double d = 0.0;

    bool c_ok = true;
    bool i_ok = true;

    // Detecta tipo e converte para c/i/f/d
    if (isChar(literal)) {
        c = literal[0];
        i = static_cast<int>(c);
        f = static_cast<float>(c);
        d = static_cast<double>(c);
    } else if (isInt(literal)) {
        long val = std::strtol(literal.c_str(), NULL, 10);
        i = static_cast<int>(val);
        c = static_cast<char>(val);
        f = static_cast<float>(val);
        d = static_cast<double>(val);
        if (val < 0 || val > 127)
            c_ok = false;
    } else if (isFloat(literal)) {
        f = std::strtof(literal.c_str(), NULL);
        d = static_cast<double>(f);
        i = static_cast<int>(f);
        c = static_cast<char>(f);

        if (literal == "nanf" || literal == "-inff" || literal == "+inff") {
            c_ok = false;
            i_ok = false;
        } else {
            if (f < 0.0f || f > 127.0f || std::isnan(f) || std::isinf(f))
                c_ok = false;
            if (f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX)
                || std::isnan(f) || std::isinf(f))
                i_ok = false;
        }
    } else if (isDouble(literal)) {
        d = std::strtod(literal.c_str(), NULL);
        f = static_cast<float>(d);
        i = static_cast<int>(d);
        c = static_cast<char>(d);

        if (literal == "nan" || literal == "-inf" || literal == "+inf") {
            c_ok = false;
            i_ok = false;
        } else {
            if (d < 0.0 || d > 127.0 || std::isnan(d) || std::isinf(d))
                c_ok = false;
            if (d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX)
                || std::isnan(d) || std::isinf(d))
                i_ok = false;
        }
    } else {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    // char
    std::cout << "char: ";
    if (!c_ok) {
        std::cout << "impossible";
    } else if (!std::isprint(c)) {
        std::cout << "Non displayable";
    } else {
        std::cout << "'" << c << "'";
    }
    std::cout << std::endl;

    // int
    std::cout << "int: ";
    if (!i_ok) {
        std::cout << "impossible";
    } else {
        std::cout << i;
    }
    std::cout << std::endl;

    // float
    std::cout << "float: ";
    if (std::isnan(f)) {
        std::cout << "nanf";
    } else if (std::isinf(f)) {
        std::cout << (f < 0 ? "-inff" : "+inff");
    } else {
        std::cout << std::fixed << std::setprecision(1) << f << "f";
    }
    std::cout << std::endl;

    // double
    std::cout << "double: ";
    if (std::isnan(d)) {
        std::cout << "nan";
    } else if (std::isinf(d)) {
        std::cout << (d < 0 ? "-inf" : "+inf");
    } else {
        std::cout << std::fixed << std::setprecision(1) << d;
    }
    std::cout << std::endl;
}