#include "../raz.hpp"

int main() {
    raz::random rng;
    raz::i32 secret_number = rng.range(1, 100);
    raz::i32 attempts = 0;
    
    raz::println("=== GUESS THE NUMBER ===");
    raz::println("I'm thinking of a number between 1 and 100");
    
    while(true) {
        raz::i32 guess = raz::input_as<raz::i32>("Your guess: ");
        attempts++;
        
        if(guess == secret_number) {
            raz::cout << "Correct! You guessed it in " << attempts << " attempts" << raz::endl;
            break;
        }
        else if(guess < secret_number) {
            raz::println("Higher...");
        }
        else {
            raz::println("Lower...");
        }
    }
    
    return 0;
}
