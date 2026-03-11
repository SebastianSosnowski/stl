#include "transform_containers.hpp"

std::map<int, std::string> removeDuplicateAndTranformToMap(std::list<std::string> words, std::deque<int> nums) {
    std::map<int, std::string> transformed{};

    std::ranges::sort(nums);
    auto new_end = std::unique(nums.begin(), nums.end());
    nums.erase(new_end, nums.end());

    words.sort();
    words.unique();

    std::vector<std::pair<int, std::string>> temp;
    temp.reserve(std::min(nums.size(), words.size()));
    auto f = [](int num, std::string& word) { return std::make_pair(num, word); };
    std::transform(nums.begin(), nums.end(), words.begin(), std::back_inserter(temp), f);
    transformed.insert(temp.begin(), temp.end());
    return transformed;
}