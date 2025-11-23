#ifndef RAZ_HPP
#define RAZ_HPP

#include <initializer_list>

namespace raz {

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;
using byte = unsigned char;

class string;

struct endl_t {};
static constexpr endl_t endl;

template<typename T, typename U>
struct pair {
    T first;
    U second;
    
    pair() : first(), second() {}
    pair(const T& f, const U& s) : first(f), second(s) {}
};

template<typename T, typename U>
pair<T, U> make_pair(const T& first, const U& second) {
    return pair<T, U>(first, second);
}

template<typename T>
class optional {
private:
    T value;
    bool has_val;

public:
    optional() : has_val(false) {}
    optional(const T& val) : value(val), has_val(true) {}
    
    bool is_present() const { return has_val; }
    T& get() { return value; }
    const T& get() const { return value; }
    
    T value_or(const T& default_val) const {
        return has_val ? value : default_val;
    }
};

u32 strlen_simple(const char* str) {
    u32 len = 0;
    while(str[len] != '\0') len++;
    return len;
}

void strcpy_simple(char* dest, const char* src) {
    u32 i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

i32 strcmp_simple(const char* a, const char* b) {
    u32 i = 0;
    while(a[i] != '\0' && b[i] != '\0') {
        if(a[i] != b[i]) return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

class string {
private:
    char* data;
    u32 len;
    u32 cap;

    void resize(u32 new_cap) {
        char* new_data = new char[new_cap];
        for(u32 i = 0; i < len; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

public:
    string() : data(new char[16]), len(0), cap(16) {
        data[0] = '\0';
    }

    string(const char* str) {
        len = strlen_simple(str);
        cap = len + 1;
        if(cap < 16) cap = 16;
        
        data = new char[cap];
        for(u32 i = 0; i < len; i++) {
            data[i] = str[i];
        }
        data[len] = '\0';
    }

    string(const string& other) : len(other.len), cap(other.cap) {
        data = new char[cap];
        for(u32 i = 0; i <= len; i++) {
            data[i] = other.data[i];
        }
    }

    ~string() {
        delete[] data;
    }

    u32 length() const { return len; }
    u32 capacity() const { return cap; }
    bool empty() const { return len == 0; }

    void push_back(char c) {
        if(len + 1 >= cap) resize(cap * 2);
        data[len++] = c;
        data[len] = '\0';
    }

    void append(const char* str) {
        u32 str_len = strlen_simple(str);
        if(len + str_len >= cap) resize((len + str_len) * 2);
        for(u32 i = 0; i < str_len; i++) {
            data[len++] = str[i];
        }
        data[len] = '\0';
    }

    char& operator[](u32 index) { return data[index]; }
    const char& operator[](u32 index) const { return data[index]; }

    string& operator=(const string& other) {
        if(this != &other) {
            delete[] data;
            len = other.len;
            cap = other.cap;
            data = new char[cap];
            for(u32 i = 0; i <= len; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    string& operator+=(const char* str) { append(str); return *this; }
    string& operator+=(char c) { push_back(c); return *this; }

    const char* c_str() const { return data; }
    void clear() { len = 0; data[0] = '\0'; }

    bool starts_with(const char* prefix) const {
        u32 prefix_len = strlen_simple(prefix);
        if(prefix_len > len) return false;
        for(u32 i = 0; i < prefix_len; i++) {
            if(data[i] != prefix[i]) return false;
        }
        return true;
    }

    bool ends_with(const char* suffix) const {
        u32 suffix_len = strlen_simple(suffix);
        if(suffix_len > len) return false;
        for(u32 i = 0; i < suffix_len; i++) {
            if(data[len - suffix_len + i] != suffix[i]) return false;
        }
        return true;
    }

    string substr(u32 start, u32 count = -1) const {
        if(start >= len) return string("");
        u32 actual_count = (count == (u32)-1) ? len - start : count;
        if(start + actual_count > len) actual_count = len - start;
        
        string result;
        for(u32 i = 0; i < actual_count; i++) {
            result.push_back(data[start + i]);
        }
        return result;
    }

    bool operator==(const string& other) const {
        if(len != other.len) return false;
        for(u32 i = 0; i < len; i++) {
            if(data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator==(const char* other) const {
        u32 other_len = strlen_simple(other);
        if(len != other_len) return false;
        for(u32 i = 0; i < len; i++) {
            if(data[i] != other[i]) return false;
        }
        return true;
    }

    bool operator!=(const string& other) const {
        return !(*this == other);
    }

    bool operator!=(const char* other) const {
        return !(*this == other);
    }

    i32 compare(const char* other) const {
        return strcmp_simple(data, other);
    }

    i32 compare(const string& other) const {
        return strcmp_simple(data, other.data);
    }
};

class ostream {
private:
    void write_char(char c) {
        #if defined(__linux__)
        asm volatile (
            "mov $4, %%eax\n"
            "mov $1, %%ebx\n"
            "mov %0, %%ecx\n"
            "mov $1, %%edx\n"
            "int $0x80"
            :
            : "r"(&c)
            : "eax", "ebx", "ecx", "edx"
        );
        #endif
    }

    void write_string(const char* str) {
        u32 len = strlen_simple(str);
        #if defined(__linux__)
        asm volatile (
            "mov $4, %%eax\n"
            "mov $1, %%ebx\n"
            "mov %0, %%ecx\n"
            "mov %1, %%edx\n"
            "int $0x80"
            :
            : "r"(str), "r"(len)
            : "eax", "ebx", "ecx", "edx"
        );
        #else
        for(u32 i = 0; i < len; i++) write_char(str[i]);
        #endif
    }

public:
    ostream& operator<<(const char* str) { write_string(str); return *this; }
    ostream& operator<<(const string& str) { write_string(str.c_str()); return *this; }
    ostream& operator<<(char c) { write_char(c); return *this; }
    ostream& operator<<(const endl_t&) { write_char('\n'); return *this; }
    ostream& operator<<(bool b) { write_string(b ? "true" : "false"); return *this; }

    ostream& operator<<(i32 num) {
        char buffer[32];
        i32 i = 0;
        bool negative = num < 0;
        if(negative) num = -num;

        do {
            buffer[i++] = '0' + (num % 10);
            num /= 10;
        } while(num > 0);
        
        if(negative) buffer[i++] = '-';

        for(i32 j = 0; j < i / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
        buffer[i] = '\0';
        write_string(buffer);
        return *this;
    }

    ostream& operator<<(u32 num) {
        char buffer[32];
        u32 i = 0;

        do {
            buffer[i++] = '0' + (num % 10);
            num /= 10;
        } while(num > 0);

        for(u32 j = 0; j < i / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
        buffer[i] = '\0';
        write_string(buffer);
        return *this;
    }

    ostream& operator<<(f64 num) {
        i32 int_part = (i32)num;
        *this << int_part << ".";
        
        f64 decimal = num - int_part;
        if(decimal < 0) decimal = -decimal;
        
        for(i32 i = 0; i < 4; i++) {
            decimal *= 10;
            i32 digit = (i32)decimal;
            *this << digit;
            decimal -= digit;
        }
        return *this;
    }
};

static ostream cout;

void print(const char* str) { cout << str; }
void print(const string& str) { cout << str; }
void print(i32 num) { cout << num; }
void print(u32 num) { cout << num; }
void print(f64 num) { cout << num; }
void print(bool b) { cout << b; }

void println(const char* str) { cout << str << endl; }
void println(const string& str) { cout << str << endl; }
void println(i32 num) { cout << num << endl; }
void println(u32 num) { cout << num << endl; }
void println(f64 num) { cout << num << endl; }
void println(bool b) { cout << b << endl; }

class istream {
private:
    char read_char() {
        char c;
        #if defined(__linux__)
        asm volatile (
            "mov $3, %%eax\n"
            "mov $0, %%ebx\n"
            "mov %0, %%ecx\n"
            "mov $1, %%edx\n"
            "int $0x80"
            :
            : "r"(&c)
            : "eax", "ebx", "ecx", "edx"
        );
        #endif
        return c;
    }

public:
    istream& operator>>(string& str) {
        str.clear();
        char c;
        while(true) {
            c = read_char();
            if(c == '\n' || c == ' ') break;
            str.push_back(c);
        }
        return *this;
    }

    istream& operator>>(i32& num) {
        string str;
        *this >> str;
        num = 0;
        bool negative = false;
        u32 i = 0;
        
        if(str[0] == '-') {
            negative = true;
            i = 1;
        }
        
        for(; i < str.length(); i++) {
            num = num * 10 + (str[i] - '0');
        }
        
        if(negative) num = -num;
        return *this;
    }

    istream& operator>>(u32& num) {
        string str;
        *this >> str;
        num = 0;
        for(u32 i = 0; i < str.length(); i++) {
            num = num * 10 + (str[i] - '0');
        }
        return *this;
    }

    istream& operator>>(f64& num) {
        string str;
        *this >> str;
        num = 0.0;
        bool negative = false;
        u32 i = 0;
        
        if(str[0] == '-') {
            negative = true;
            i = 1;
        }
        
        // Parte entera
        for(; i < str.length() && str[i] != '.'; i++) {
            num = num * 10.0 + (str[i] - '0');
        }
        
        // Parte decimal
        if(i < str.length() && str[i] == '.') {
            f64 decimal = 0.0;
            f64 factor = 0.1;
            i++;
            for(; i < str.length(); i++) {
                decimal += (str[i] - '0') * factor;
                factor *= 0.1;
            }
            num += decimal;
        }
        
        if(negative) num = -num;
        return *this;
    }

    istream& operator>>(char& c) {
        c = read_char();
        return *this;
    }

    istream& getline(string& str) {
        str.clear();
        char c;
        while(true) {
            c = read_char();
            if(c == '\n') break;
            str.push_back(c);
        }
        return *this;
    }
};

static istream cin;

string input(const char* prompt = "") {
    if(strlen_simple(prompt) > 0) {
        raz::cout << prompt;
    }
    string result;
    raz::cin.getline(result);
    return result;
}

template<typename T>
T input_as(const char* prompt = "") {
    if(strlen_simple(prompt) > 0) {
        raz::cout << prompt;
    }
    T result;
    raz::cin >> result;
    return result;
}

template<typename K, typename V>
class map {
private:
    pair<K, V>* data;
    u32 len;
    u32 cap;

    void resize(u32 new_cap) {
        pair<K, V>* new_data = new pair<K, V>[new_cap];
        for(u32 i = 0; i < len; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

public:
    map() : data(new pair<K, V>[8]), len(0), cap(8) {}
    
    ~map() {
        delete[] data;
    }

    void insert(const K& key, const V& value) {
        for(u32 i = 0; i < len; i++) {
            if(data[i].first == key) {
                data[i].second = value;
                return;
            }
        }
        
        if(len >= cap) resize(cap * 2);
        data[len++] = make_pair(key, value);
    }

    optional<V> get(const K& key) const {
        for(u32 i = 0; i < len; i++) {
            if(data[i].first == key) {
                return optional<V>(data[i].second);
            }
        }
        return optional<V>();
    }

    bool contains(const K& key) const {
        for(u32 i = 0; i < len; i++) {
            if(data[i].first == key) return true;
        }
        return false;
    }

    u32 size() const { return len; }
    bool empty() const { return len == 0; }

    void erase(const K& key) {
        for(u32 i = 0; i < len; i++) {
            if(data[i].first == key) {
                for(u32 j = i; j < len - 1; j++) {
                    data[j] = data[j + 1];
                }
                len--;
                return;
            }
        }
    }
};

template<typename T>
class array {
private:
    T* data;
    u32 len;

public:
    array(u32 size) : data(new T[size]), len(size) {}
    
    array(std::initializer_list<T> init_list) : data(new T[init_list.size()]), len(init_list.size()) {
        u32 i = 0;
        for(const T& item : init_list) {
            data[i++] = item;
        }
    }

    ~array() {
        delete[] data;
    }

    T& operator[](u32 index) { return data[index]; }
    const T& operator[](u32 index) const { return data[index]; }
    
    u32 size() const { return len; }
    T* begin() { return data; }
    T* end() { return data + len; }
    const T* begin() const { return data; }
    const T* end() const { return data + len; }
};

template<typename T>
class vector {
private:
    T* data;
    u32 len;
    u32 cap;

    void resize(u32 new_cap) {
        T* new_data = new T[new_cap];
        for(u32 i = 0; i < len; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

public:
    vector() : data(new T[8]), len(0), cap(8) {}
    
    vector(u32 size) : data(new T[size]), len(size), cap(size) {}
    
    vector(const vector& other) : len(other.len), cap(other.cap) {
        data = new T[cap];
        for(u32 i = 0; i < len; i++) {
            data[i] = other.data[i];
        }
    }

    vector(std::initializer_list<T> init_list) : len(init_list.size()), cap(init_list.size()) {
        data = new T[cap];
        u32 i = 0;
        for(const T& item : init_list) {
            data[i++] = item;
        }
    }

    ~vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if(len >= cap) resize(cap * 2);
        data[len++] = value;
    }

    void pop_back() {
        if(len > 0) len--;
    }

    T& operator[](u32 index) { return data[index]; }
    const T& operator[](u32 index) const { return data[index]; }

    u32 size() const { return len; }
    u32 capacity() const { return cap; }
    bool empty() const { return len == 0; }

    T* begin() { return data; }
    T* end() { return data + len; }
    const T* begin() const { return data; }
    const T* end() const { return data + len; }

    void clear() { len = 0; }
    
    T& front() { return data[0]; }
    T& back() { return data[len - 1]; }
    const T& front() const { return data[0]; }
    const T& back() const { return data[len - 1]; }
};

i32 abs(i32 x) { return x < 0 ? -x : x; }
f64 abs(f64 x) { return x < 0 ? -x : x; }

f64 pow(f64 base, i32 exp) {
    f64 result = 1.0;
    bool negative = exp < 0;
    u32 abs_exp = negative ? -exp : exp;
    
    for(u32 i = 0; i < abs_exp; i++) result *= base;
    return negative ? 1.0 / result : result;
}

i32 min(i32 a, i32 b) { return a < b ? a : b; }
i32 max(i32 a, i32 b) { return a > b ? a : b; }
f64 min(f64 a, f64 b) { return a < b ? a : b; }
f64 max(f64 a, f64 b) { return a > b ? a : b; }

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void sort(T* arr, u32 size) {
    for(u32 i = 0; i < size - 1; i++) {
        for(u32 j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

template<typename T>
i32 find(const T* arr, u32 size, const T& value)
{
    for(u32 i = 0; i < size; i++) 
    {
        if(arr[i] == value) return i;
    }
    return -1;
}

class random {
private:
    u32 seed;

public:
    random(u32 initial_seed = 12345) : seed(initial_seed) {}
    
    

    u32 next()
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        return seed;
    }
    
    u32 range(u32 min, u32 max) 
    {
        return min + (next() % (max - min + 1));
    }
    
    f64 float_range(f64 min, f64 max) 
    {
        return min + (next() / (f64)0x7FFFFFFF) * (max - min);
    }
};

template<typename T>
class queue {
private:
    vector<T> data;

public:
    void push(const T& value) { data.push_back(value); }
    void pop() 
    { 
        if(!data.empty()) {
            for(u32 i = 1; i < data.size(); i++) {
                data[i-1] = data[i];
            }
            data.pop_back();
        }
    }
    T& front() { return data[0]; }
    const T& front() const { return data[0]; }
    bool empty() const { return data.empty(); }
    u32 size() const { return data.size(); }
};

template<typename T>
class stack {
private:
    vector<T> data;




public:
    void push(const T& value) { data.push_back(value); }
    void pop() { if(!data.empty()) data.pop_back(); }
    T& top() { return data.back(); }
    const T& top() const { return data.back(); }
    bool empty() const { return data.empty(); }
    u32 size() const { return data.size(); }
};

u32 hash_simple
(const char* str) 
{
    u32 hash = 5381;
    u32 i = 0;
    while(str[i] != '\0') {
        hash = ((hash << 5) + hash) + str[i];
        i++;
    }
    return hash;
}

}

#define let auto
#define var auto
#define loop for(;;)
#define foreach(item, container) for(auto& item : container)
#define repeat(n) for(raz::u32 _i = 0; _i < n; _i++)

#endif
