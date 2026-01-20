#include "Base.hpp"
#include "Identify.hpp"

/* usa polimorfismo com dynamic_cast para identificar o tipo 
real (A, B ou C) de objetos que herdam de Base (com virtual 
~Base()), sem usar std::typeinfo. generate() cria 
randomicamente new A/B/C retornando Base* via std::rand()%3; 
identify(Base* p) usa dynamic_cast<A* /B* /C* >(p) (NULL se 
falhar); identify(Base& p) usa dynamic_cast<A&/B&/C&>(p) 
em try/catch(std::bad_cast) (lança exceção se falhar). 
As classes A/B/C são vazias (sem forma canônica), 
srand(time(NULL)) seed uma vez no main, e o loop em main 
demonstra consistência entre ponteiro e referência, 
liberando com delete.*/

int main() {
    std::srand(std::time(NULL));

    std::cout << "Generating random instances..." << std::endl;
    for (int i = 0; i < 10; ++i) {
        Base* ptr = generate();
        std::cout << "Ptr: " << ptr << std::endl;
        identify(ptr);
        identify(*ptr);
        delete ptr;
        std::cout << std::endl;
    }
    return 0;
}
