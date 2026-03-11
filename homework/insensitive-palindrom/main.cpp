#include "palindrom.hpp"

int main() {
    std::string in = "cat";
    std::cout << "Is it palindrome: " << std::boolalpha << is_palindrome(in) << "\n";
    return 0;
}