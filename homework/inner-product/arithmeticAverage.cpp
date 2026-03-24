#include "arithmeticAverage.hpp"

double ArithmeticAverage(const std::vector<int>& first, const std::vector<int>& second) {
    auto sum = std::reduce(first.begin(), first.end(), 0.0) + std::reduce(second.begin(), second.end(), 0.0);
    return sum / (first.size() + second.size());
}

double Distance(const std::vector<int>& point1, const std::vector<int>& point2) {
    return 0.0;
}