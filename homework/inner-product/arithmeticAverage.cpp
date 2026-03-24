#include "arithmeticAverage.hpp"

double ArithmeticAverage(const std::vector<int>& first, const std::vector<int>& second) {
    auto sum = std::reduce(first.begin(), first.end(), 0.0) + std::reduce(second.begin(), second.end(), 0.0);
    return sum / (first.size() + second.size());
}

double Distance(const std::vector<int>& point1, const std::vector<int>& point2) {
    auto f = [](const auto& lhs, const auto& rhs) { 
        double diff = lhs-rhs;
        return diff * diff; };
    auto sum_of_squares = std::transform_reduce(point1.begin(), point1.end(), point2.begin(), 0.0, std::plus<>(), f);
    return std::sqrt(sum_of_squares);
}