#ifndef IDENTIFY_HPP
#define IDENTIFY_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

class Base;

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif
