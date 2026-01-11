#include "vowel.hpp"

void removeVowels(std::vector<std::string>& vec) {
    std::string vowels = "aeiouyAEIOUY";
    for (auto& str : vec) {
        for (auto it = str.begin(); it != str.end();) {
            if (vowels.find(*it) != std::string::npos) {
                it = str.erase(it);
            } else {
                ++it;
            }
        }
    }
}