# Raz Library Documentation

A lightweight, header-only C++ standard library alternative with zero dependencies.


             LICENSE: **GPL-3.0**        by:NopAngel

## Table of Contents
- [Basic Types](#basic-types)
- [String Class](#string-class)
- [Vector Class](#vector-class)
- [Map Class](#map-class)
- [Array Class](#array-class)
- [Optional Class](#optional-class)
- [Pair Struct](#pair-struct)
- [Input/Output System](#inputoutput-system)
- [Algorithms](#algorithms)
- [Mathematics](#mathematics)
- [Random Number Generation](#random-number-generation)
- [Containers](#containers)
- [Utility Functions](#utility-functions)
- [Macros](#macros)

## Basic Types

### Type Aliases
```cpp
raz::i8, raz::i16, raz::i32, raz::i64  // Signed integers
raz::u8, raz::u16, raz::u32, raz::u64  // Unsigned integers  
raz::f32, raz::f64                     // Floating point
raz::byte                              // Byte type
```

**Usage:**
```cpp
raz::i32 age = 25;
raz::f64 price = 19.99;
raz::u32 count = 100;
```

## String Class

### Creation and Basic Operations
```cpp
raz::string str1;                    // Empty string
raz::string str2 = "Hello";          // From C-string
raz::string str3 = str2;             // Copy constructor

str1.push_back('!');                 // Add character
str1.append(" World");               // Append string
str1 += "!";                         // Append operator

raz::cout << str1.length();          // Get length
raz::cout << str1.c_str();           // Get C-string
```

### String Manipulation
```cpp
raz::string text = "Hello World";

// Substring
raz::string sub = text.substr(6, 5); // "World"

// Check prefixes/suffixes
bool starts = text.starts_with("Hello"); // true
bool ends = text.ends_with("World");     // true

// Comparison
if(text == "Hello World") { /* ... */ }
if(text.compare("Hello") != 0) { /* ... */ }

// Clear
text.clear(); // Empty the string
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::string name = "John";
    raz::string greeting = "Hello ";
    greeting += name;
    
    raz::cout << greeting << raz::endl;           // "Hello John"
    raz::cout << "Length: " << greeting.length() << raz::endl;
    raz::cout << "Starts with Hello: " << greeting.starts_with("Hello") << raz::endl;
    
    raz::string part = greeting.substr(6, 4);     // "John"
    raz::cout << "Substring: " << part << raz::endl;
    
    return 0;
}
```

## Vector Class

### Dynamic Array Operations
```cpp
// Creation
raz::vector<raz::i32> numbers;                    // Empty
raz::vector<raz::string> names(10);               // With size
raz::vector<raz::i32> values = {1, 2, 3, 4, 5};  // Initializer list

// Adding elements
numbers.push_back(10);
numbers.push_back(20);
numbers.push_back(30);

// Access
raz::i32 first = numbers[0];         // 10
raz::i32 last = numbers.back();      // 30

// Size information
raz::u32 size = numbers.size();      // 3
bool empty = numbers.empty();        // false

// Removal
numbers.pop_back();                  // Remove last element
```

### Iteration Methods
```cpp
raz::vector<raz::i32> nums = {1, 2, 3, 4, 5};

// Index-based loop
for(raz::u32 i = 0; i < nums.size(); i++) {
    raz::cout << nums[i] << " ";
}

// Range-based loop (using macro)
foreach(num, nums) {
    raz::cout << num << " ";
}

// Iterator-based
for(auto it = nums.begin(); it != nums.end(); it++) {
    raz::cout << *it << " ";
}
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::vector<raz::i32> scores;
    
    // Add scores
    scores.push_back(85);
    scores.push_back(92);
    scores.push_back(78);
    
    // Calculate average
    raz::i32 sum = 0;
    foreach(score, scores) {
        sum += score;
    }
    raz::f64 average = (raz::f64)sum / scores.size();
    
    raz::cout << "Scores: ";
    foreach(score, scores) {
        raz::cout << score << " ";
    }
    raz::cout << raz::endl;
    raz::cout << "Average: " << average << raz::endl;
    
    return 0;
}
```

## Map Class

### Key-Value Storage
```cpp
raz::map<raz::string, raz::i32> ages;

// Insertion
ages.insert("Alice", 25);
ages.insert("Bob", 30);
ages.insert("Charlie", 35);

// Retrieval
auto alice_age = ages.get("Alice");
if(alice_age.is_present()) {
    raz::cout << "Alice's age: " << alice_age.get() << raz::endl;
}

// Check existence
if(ages.contains("Bob")) {
    raz::println("Bob exists in map");
}

// Removal
ages.erase("Charlie");

// Size
raz::u32 count = ages.size();
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::map<raz::string, raz::string> phonebook;
    
    // Add contacts
    phonebook.insert("Alice", "555-0101");
    phonebook.insert("Bob", "555-0102");
    phonebook.insert("Charlie", "555-0103");
    
    // Search for a contact
    raz::string name = raz::input("Enter name to search: ");
    auto phone = phonebook.get(name);
    
    if(phone.is_present()) {
        raz::cout << "Phone number: " << phone.get() << raz::endl;
    } else {
        raz::println("Contact not found");
    }
    
    // Display all contacts
    raz::println("\nAll contacts:");
    // Note: Map doesn't have built-in iteration in this version
    
    return 0;
}
```

## Array Class

### Fixed-size Array
```cpp
// Creation
raz::array<raz::i32, 5> fixed_array;              // Fixed size
raz::array<raz::string> names = {"A", "B", "C"};  // Initializer list

// Access
fixed_array[0] = 10;
raz::i32 value = fixed_array[1];

// Size
raz::u32 size = fixed_array.size();

// Iteration
foreach(element, fixed_array) {
    raz::cout << element << " ";
}
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::array<raz::string> weekdays = {
        "Monday", "Tuesday", "Wednesday", 
        "Thursday", "Friday", "Saturday", "Sunday"
    };
    
    raz::println("Weekdays:");
    foreach(day, weekdays) {
        raz::cout << day << " ";
    }
    raz::cout << raz::endl;
    
    raz::i32 day_index = raz::input_as<raz::i32>("Enter day number (1-7): ") - 1;
    if(day_index >= 0 && day_index < weekdays.size()) {
        raz::cout << "That day is: " << weekdays[day_index] << raz::endl;
    } else {
        raz::println("Invalid day number");
    }
    
    return 0;
}
```

## Optional Class

### Handling Optional Values
```cpp
raz::optional<raz::i32> maybe_number;

// Check if value exists
if(!maybe_number.is_present()) {
    raz::println("No value");
}

// Set value
maybe_number = raz::optional<raz::i32>(42);

// Get value (with safety check)
if(maybe_number.is_present()) {
    raz::i32 value = maybe_number.get();
    raz::cout << "Value: " << value << raz::endl;
}

// Default value
raz::i32 result = maybe_number.value_or(100);
```

### Complete Example
```cpp
#include "raz.hpp"

raz::optional<raz::f64> divide(raz::f64 a, raz::f64 b) {
    if(b == 0) {
        return raz::optional<raz::f64>(); // Empty optional
    }
    return raz::optional<raz::f64>(a / b);
}

int main() {
    raz::f64 num1 = raz::input_as<raz::f64>("Enter first number: ");
    raz::f64 num2 = raz::input_as<raz::f64>("Enter second number: ");
    
    auto result = divide(num1, num2);
    
    if(result.is_present()) {
        raz::cout << "Result: " << result.get() << raz::endl;
    } else {
        raz::println("Error: Division by zero!");
    }
    
    return 0;
}
```

## Pair Struct

### Two-element Tuple
```cpp
// Creation
raz::pair<raz::string, raz::i32> person = raz::make_pair("Alice", 25);

// Access
raz::string name = person.first;
raz::i32 age = person.second;

// Modification
person.first = "Bob";
person.second = 30;
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::vector<raz::pair<raz::string, raz::i32>> students;
    
    students.push_back(raz::make_pair("Alice", 85));
    students.push_back(raz::make_pair("Bob", 92));
    students.push_back(raz::make_pair("Charlie", 78));
    
    raz::println("Student grades:");
    foreach(student, students) {
        raz::cout << student.first << ": " << student.second << raz::endl;
    }
    
    return 0;
}
```

## Input/Output System

### Output Operations
```cpp
// Basic output
raz::cout << "Hello World" << raz::endl;
raz::print("No newline");
raz::println("With newline");

// Formatted output
raz::i32 age = 25;
raz::f64 height = 1.75;
raz::bool is_student = true;

raz::cout << "Age: " << age << raz::endl;
raz::cout << "Height: " << height << raz::endl;
raz::cout << "Student: " << is_student << raz::endl;
```

### Input Operations
```cpp
// String input
raz::string name = raz::input("Enter your name: ");

// Typed input
raz::i32 age = raz::input_as<raz::i32>("Enter your age: ");
raz::f64 height = raz::input_as<raz::f64>("Enter your height: ");

// Direct stream input
raz::i32 number;
raz::cin >> number;

// Line input
raz::string full_line;
raz::cin.getline(full_line);
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::println("=== USER REGISTRATION ===");
    
    raz::string name = raz::input("Enter your name: ");
    raz::i32 age = raz::input_as<raz::i32>("Enter your age: ");
    raz::f64 height = raz::input_as<raz::f64>("Enter your height (meters): ");
    
    raz::println("\n=== REGISTRATION COMPLETE ===");
    raz::cout << "Name: " << name << raz::endl;
    raz::cout << "Age: " << age << raz::endl;
    raz::cout << "Height: " << height << "m" << raz::endl;
    
    return 0;
}
```

## Algorithms

### Sorting and Searching
```cpp
raz::i32 numbers[] = {5, 2, 8, 1, 9};
raz::u32 size = 5;

// Sorting
raz::sort(numbers, size); // Array now: {1, 2, 5, 8, 9}

// Searching
raz::i32 index = raz::find(numbers, size, 5); // Returns 2
if(index != -1) {
    raz::cout << "Found at index: " << index << raz::endl;
}

// Swapping
raz::i32 a = 10, b = 20;
raz::swap(a, b); // a=20, b=10
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::i32 scores[10];
    raz::u32 count = 5;
    
    raz::println("Enter 5 scores:");
    for(raz::u32 i = 0; i < count; i++) {
        scores[i] = raz::input_as<raz::i32>("Score " + raz::to_string(i+1) + ": ");
    }
    
    // Sort scores
    raz::sort(scores, count);
    
    raz::println("\nSorted scores:");
    for(raz::u32 i = 0; i < count; i++) {
        raz::cout << scores[i] << " ";
    }
    raz::cout << raz::endl;
    
    // Search for a score
    raz::i32 search_score = raz::input_as<raz::i32>("Enter score to find: ");
    raz::i32 position = raz::find(scores, count, search_score);
    
    if(position != -1) {
        raz::cout << "Score found at position: " << position + 1 << raz::endl;
    } else {
        raz::println("Score not found");
    }
    
    return 0;
}
```

## Mathematics

### Math Functions
```cpp
raz::i32 negative = -5;
raz::i32 positive = raz::abs(negative); // 5

raz::f64 base = 2.0;
raz::f64 power = raz::pow(base, 3); // 8.0

raz::i32 smaller = raz::min(10, 5); // 5
raz::i32 larger = raz::max(10, 5);  // 10

raz::f64 min_float = raz::min(3.14, 2.71); // 2.71
raz::f64 max_float = raz::max(3.14, 2.71); // 3.14
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::f64 a = raz::input_as<raz::f64>("Enter first number: ");
    raz::f64 b = raz::input_as<raz::f64>("Enter second number: ");
    
    raz::cout << "Absolute of first: " << raz::abs(a) << raz::endl;
    raz::cout << "Power (first^second): " << raz::pow(a, b) << raz::endl;
    raz::cout << "Minimum: " << raz::min(a, b) << raz::endl;
    raz::cout << "Maximum: " << raz::max(a, b) << raz::endl;
    
    return 0;
}
```

## Random Number Generation

### Random Operations
```cpp
raz::random rng;

// Basic random number
raz::u32 random_num = rng.next();

// Range-based random
raz::u32 dice_roll = rng.range(1, 6); // 1-6 inclusive

// Floating point range
raz::f64 random_float = rng.float_range(0.0, 1.0);
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::random rng;
    
    raz::println("=== RANDOM NUMBER DEMO ===");
    
    raz::println("5 random numbers between 1-100:");
    for(raz::u32 i = 0; i < 5; i++) {
        raz::u32 num = rng.range(1, 100);
        raz::cout << num << " ";
    }
    raz::cout << raz::endl;
    
    raz::println("\n3 random floats between 0-1:");
    for(raz::u32 i = 0; i < 3; i++) {
        raz::f64 num = rng.float_range(0.0, 1.0);
        raz::cout << num << " ";
    }
    raz::cout << raz::endl;
    
    // Dice game
    raz::u32 player_roll = rng.range(1, 6);
    raz::u32 computer_roll = rng.range(1, 6);
    
    raz::cout << "\nPlayer rolled: " << player_roll << raz::endl;
    raz::cout << "Computer rolled: " << computer_roll << raz::endl;
    
    if(player_roll > computer_roll) {
        raz::println("Player wins!");
    } else if(computer_roll > player_roll) {
        raz::println("Computer wins!");
    } else {
        raz::println("It's a tie!");
    }
    
    return 0;
}
```

## Containers

### Queue (FIFO)
```cpp
raz::queue<raz::i32> q;

q.push(10);
q.push(20);
q.push(30);

raz::i32 front = q.front(); // 10
q.pop(); // Remove 10
raz::i32 new_front = q.front(); // 20
```

### Stack (LIFO)
```cpp
raz::stack<raz::i32> s;

s.push(10);
s.push(20);
s.push(30);

raz::i32 top = s.top(); // 30
s.pop(); // Remove 30
raz::i32 new_top = s.top(); // 20
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    raz::println("=== QUEUE EXAMPLE ===");
    raz::queue<raz::string> task_queue;
    
    task_queue.push("Task 1");
    task_queue.push("Task 2");
    task_queue.push("Task 3");
    
    raz::println("Processing tasks in order:");
    while(!task_queue.empty()) {
        raz::string task = task_queue.front();
        raz::cout << "Processing: " << task << raz::endl;
        task_queue.pop();
    }
    
    raz::println("\n=== STACK EXAMPLE ===");
    raz::stack<raz::string> browser_history;
    
    browser_history.push("google.com");
    browser_history.push("example.com");
    browser_history.push("test.com");
    
    raz::println("Browser history (LIFO):");
    while(!browser_history.empty()) {
        raz::string page = browser_history.top();
        raz::cout << "Visited: " << page << raz::endl;
        browser_history.pop();
    }
    
    return 0;
}
```

## Utility Functions

### String Utilities
```cpp
const char* text = "Hello";

raz::u32 length = raz::strlen_simple(text); // 5

char dest[10];
raz::strcpy_simple(dest, text); // dest = "Hello"

raz::i32 comparison = raz::strcmp_simple("abc", "abd"); // -1

raz::u32 hash = raz::hash_simple("hello"); // Hash value
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    const char* str1 = "Hello";
    const char* str2 = "World";
    
    raz::cout << "Length of '" << str1 << "': " << raz::strlen_simple(str1) << raz::endl;
    
    char buffer[20];
    raz::strcpy_simple(buffer, str1);
    raz::cout << "Copied string: " << buffer << raz::endl;
    
    raz::i32 cmp = raz::strcmp_simple(str1, str2);
    raz::cout << "Comparison result: " << cmp << raz::endl;
    
    raz::u32 hash_val = raz::hash_simple(str1);
    raz::cout << "Hash of '" << str1 << "': " << hash_val << raz::endl;
    
    return 0;
}
```

## Macros

### Convenience Macros
```cpp
// Type inference
let number = 42;                    // auto number = 42;
var name = raz::string("John");     // auto name = raz::string("John");

// Loops
loop { /* infinite loop */ }

repeat(5) {
    raz::println("This repeats 5 times");
}

foreach(item, container) {
    // Range-based for loop
}
```

### Complete Example
```cpp
#include "raz.hpp"

int main() {
    let numbers = raz::vector<raz::i32>{1, 2, 3, 4, 5};
    
    raz::println("Numbers using macros:");
    foreach(num, numbers) {
        raz::cout << num << " ";
    }
    raz::cout << raz::endl;
    
    raz::println("Repeating 3 times:");
    repeat(3) {
        raz::println("Repeat iteration");
    }
    
    return 0;
}
```

## Compilation

```bash
g++ -O2 -o program program.cpp
./program
```

## Features Summary

-  **Zero Dependencies** - Only requires C++ compiler
-  **Header-Only** - Single include file
-  **Memory Safe** - Automatic memory management
-  **Type Safe** - Strong typing throughout
-  **Portable** - Works on any platform with C++ support
-  **STL-Compatible** - Familiar interface for C++ developers

