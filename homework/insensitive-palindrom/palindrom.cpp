#include "palindrom.hpp"

static char my_tolower(char ch) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}
static bool my_isalnum(char ch) {
    return std::isalnum(static_cast<unsigned char>(ch));
}

// More elegant with STL, but slower, bcs time complexity  O(N)
bool is_palindrome(std::string word) {
    auto normalized = word | std::views::filter(my_isalnum) | std::views::transform(my_tolower);
    return std::ranges::equal(normalized, normalized | std::views::reverse);
}
//  with while loop, time complexity is O(N/2)
// bool is_palindrome(std::string word) {
//     auto left = word.begin();
//     auto right = std::prev(word.end());
//     std::cout << *left << " " << *right << "\n";
//     while (left < right) {
//         if (!my_isalnum(*left)) {
//             left++;
//             continue;
//         }
//         if (!my_isalnum(*right)) {
//             right--;
//             continue;
//         }
//         auto l = my_tolower(*left);
//         auto r = my_tolower(*right);

//         if (l != r) {
//             return false;
//         }
//         left++;
//         right--;
//     }
//     return true;
// }