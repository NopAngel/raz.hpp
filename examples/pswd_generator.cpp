#include "../raz.hpp"

int main() {
    raz::random rng;
    raz::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%";
    
    raz::println("=== PASSWORD GENERATOR ===");
    
    raz::u32 length = raz::input_as<raz::u32>("Password length: ");
    
    raz::string password;
    for(raz::u32 i = 0; i < length; i++) {
        raz::u32 index = rng.range(0, characters.length() - 1);
        password.push_back(characters[index]);
    }
    
    raz::cout << "Your password: " << password << raz::endl;
    
    return 0;
}
