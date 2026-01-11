#include "sort.hpp"

std::deque<std::string> lengthSort(std::forward_list<std::string>& words) {
    std::deque<std::string> sorted;
    for (auto& word : words) {
        if (sorted.empty()) {
            sorted.push_back(word);
            continue;
        }
        for (auto it = sorted.begin(); it != sorted.end();) {
            std::string& s = *it;

            if (word.length() < s.length()) {
                sorted.insert(it, word);
                break;
            } else if (word.length() == s.length()) {
                if (word <= s) {
                    sorted.insert(it, word);
                    break;
                }
            }
            ++it;

            if (it == sorted.end()) {
                sorted.push_back(word);
                break;
            }
        }
    }

    return sorted;
}