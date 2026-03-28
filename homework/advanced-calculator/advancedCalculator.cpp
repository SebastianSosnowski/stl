#include "advancedCalculator.hpp"

struct InputData {
    double lhs = 0.0;
    double rhs = 0.0;
    char operation = ' ';
};

static bool bad_character(const std::string& in) {
    std::unordered_set<char> allowed{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                     '+', '-', '*', '/', '%', '^', '$', '!', '.',
                                     ' '};
    for (const auto& ch : in) {
        if (!allowed.contains(ch)) {
            return true;
        }
    }
    return false;
}

std::string::size_type find_operator(const std::string& in) {
    const std::string operators = "+-*/%^$!";

    for (std::string::size_type i = 0; i < in.size(); ++i) {
        char c = in[i];
        // jeśli pierwszy znak to '-' → może oznaczać liczbę ujemną
        if (i == 0 && c == '-') {
            continue;
        }

        if (operators.find(c) != std::string::npos) {
            return i;
        }
    }

    return std::string::npos;
}

static std::string trim(std::string& str) {
    auto first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        ;
    auto last = str.find_last_not_of(' ');

    return str.substr(first, last - first + 1);
}

ErrorCode parse_input(const std::string& in, InputData& data, std::size_t operator_idx) {
    std::string lhs = in.substr(0, operator_idx);
    // trim(lhs);
    std::string rhs = in.substr(operator_idx + 1);
    // trim(rhs);
    data.operation = in.at(operator_idx);
    try {
        data.lhs = std::stod(lhs);
    } catch (const std::invalid_argument& e) {
        std::cerr << "First argument is not a number: " << lhs << " ";
        return ErrorCode::BadFormat;
    }
    try {
        data.rhs = std::stod(rhs);
    } catch (const std::invalid_argument& e) {
        if (!(data.operation == '!' && rhs.size() == 0)) {
            std::cerr << "Second argument is not a number: " << rhs << " ";
            return ErrorCode::BadFormat;
        }
    }

    std::cout << "lhs, mhs,  rhs: " << lhs << ", " << in.at(operator_idx) << ", " << rhs << "\n";

    return ErrorCode::OK;
}

double factorial(const int& n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

ErrorCode process(std::string input, double* out) {
    std::map<char, std::function<double(double, double)>> op{
        {'+', [](const auto& first, const auto& second) { return first + second; }},
        {'-', [](const auto& first, const auto& second) { return first - second; }},
        {'*', [](const auto& first, const auto& second) { return first * second; }},
        {'/', [](const auto& first, const auto& second) { return first / second; }},
        {'%', [](const int& first, const int& second) { return first % second; }},
        {'^', [](const auto& first, const auto& second) { return std::pow(first, second); }},
        {'$', [](const auto& first, const auto& second) { return std::pow(first, 1.0 / second); }},
        {'!', [](const int& n, int) { return factorial(n); }},
    };

    if (bad_character(input)) {
        return ErrorCode::BadCharacter;
    }
    auto op_index = find_operator(input);
    if (op_index == std::string::npos) {
        return ErrorCode::BadFormat;
    }
    InputData parsed;
    ErrorCode result = parse_input(input, parsed, op_index);
    if (result != ErrorCode::OK) {
        return result;
    }
    *out = op[parsed.operation](parsed.lhs, parsed.rhs);
    return result;
}