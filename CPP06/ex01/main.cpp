#include "Serializer.hpp"
#include <iostream>

/*O ex01 Serializer converte um ponteiro Data* 
para uintptr_t (endereço como inteiro) usando 
reinterpret_cast e volta para Data* preservando 
exatamente o mesmo endereço. É um exercício simples 
para demonstrar que reinterpret_cast pode reinterpretar 
bits de ponteiro como inteiro sem perda de informação. 
Usa uma struct Data não vazia (com membros como string name, 
int value, double price), serializa o endereço (&data), 
desserializa e prova que original == deserializado com 
uma main stack-based limpa. A classe Serializer é não 
instanciável (construtores privados) com dois métodos 
static.*/

int main() {
    Data data;
    data.name = "Test Data";
    data.value = 42;
    data.price = 99.99;

    std::cout << "Original Data address: " << &data << std::endl;
    std::cout << "Original Data members: " << data.name << ", " << data.value << ", " << data.price << std::endl;

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized value (uintptr_t): " << raw << std::endl;

    Data* ptr = Serializer::deserialize(raw);
    std::cout << "Deserialized address: " << ptr << std::endl;

    if (ptr == &data) {
        std::cout << "Success! Data pointers are equal." << std::endl;
        std::cout << "Deserialized Data members: " << ptr->name << ", " << ptr->value << ", " << ptr->price << std::endl;
    } else {
        std::cout << "Failure! Pointers do not match." << std::endl;
    }

    return 0;
}
