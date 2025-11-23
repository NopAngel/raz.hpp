#include "../raz.hpp"

int main() {
    raz::println("=== CALCULATOR ===");
    
    raz::f64 num1 = raz::input_as<raz::f64>("First number: ");
    raz::f64 num2 = raz::input_as<raz::f64>("Second number: ");
    
    raz::cout << "Sum: " << num1 + num2 << raz::endl;
    raz::cout << "Subtraction: " << num1 - num2 << raz::endl;
    raz::cout << "Multiplication: " << num1 * num2 << raz::endl;
    if(num2 != 0) {
        raz::cout << "Division: " << num1 / num2 << raz::endl;
    }
    
    return 0;
}
