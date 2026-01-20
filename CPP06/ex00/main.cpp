#include "ScalarConverter.hpp"
#include <iostream>

/*O ex00 ScalarConverter detecta o tipo real de um 
literal C++ em string (char como 'a', int como 42, 
float como 42.0f ou nanf, double como 42.0 ou nan) e 
converte para as 4 representações (char, int, float, double) 
usando static_cast, imprimindo com formato exato. 
Trata impossibilidades (impossible), não exibíveis 
(Non displayable) e pseudo-literals (nanf, ±inff, nan, ±inf). 
A classe é não instanciável com método static void 
convert(string), usando std::strtol/strtod/strtof para 
parsing, centralizando em double como base e verificando 
limites com INT_MIN/MAX, std::isnan/isinf.*/

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./convert <literal>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}
