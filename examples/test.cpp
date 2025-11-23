#include "../raz.hpp"

int main() {
    // Input básico
    raz::string name = raz::input("what your name: ");
    raz::cout << "hi, " << name << raz::endl;
    
    // Input con tipo específico
    raz::i32 year = raz::input_as<raz::i32>("who old you? ");
    raz::cout << "you a have " << year << " years" << raz::endl;
    
    // Con cin directamente
    raz::f64 meters;
    raz::cout << "how tall are you? ";
    raz::cin >> meters;
    raz::cout << "you measure " << meters << " meters" << raz::endl;
    
    // Comparación de strings
    raz::string res = raz::input("i like C++? ");
    if(res.compare("yea") == 0 || res.compare("yes") == 0) {
        raz::println("c++ is a shit!");
    } else {
        raz::println("c >>");
    }
    
    return 0;
}
