#include "../raz.hpp"

int main() {
    raz::vector<raz::string> tasks;
    
    raz::println("=== TODO LIST ===");
    
    while(true) {
        raz::string option = raz::input("\n1. Add task\n2. View tasks\n3. Exit\nOption: ");
        
        if(option == "1") {
            raz::string task = raz::input("Task: ");
            tasks.push_back(task);
            raz::println("Task added!");
        }
        else if(option == "2") {
            raz::println("\n--- Your tasks ---");
            for(raz::u32 i = 0; i < tasks.size(); i++) {
                raz::cout << (i + 1) << ". " << tasks[i] << raz::endl;
            }
        }
        else if(option == "3") {
            break;
        }
    }
    
    return 0;
}
