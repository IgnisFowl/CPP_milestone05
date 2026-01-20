#include "Identify.hpp"
#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void) {
    int type = std::rand() % 3;
    
    switch (type) {
        case 0: return new A;
        case 1: return new B;
        case 2: return new C;
        default: return new A;  // Fallback
    }
}

void identify(Base* p) {
    // dynamic_cast em ponteiro: NULL se falhar
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify(Base& p) {
    // dynamic_cast em referência: lança std::bad_cast se falhar
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    } catch (std::exception&) {
        try {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
        } catch (std::exception&) {
            try {
                (void)dynamic_cast<C&>(p);
                std::cout << "C" << std::endl;
            } catch (std::exception&) {}
        }
    }
}
