#include "advancedCalculator.hpp"

struct InputData {
    double lhs = 0.0;
    double rhs = 0.0;
    char operation = '0';
};

InputData parse_input(std::string& in) {
    std::array<char, 8> valid_operations{'+', '-', '*', '/', '%', '!', '^', '$'};
    std::string lhs = "", mhs = "", rhs = "";
    auto it = in.begin();

    for (; it != in.end(); it++) {
        if (isspace(*it))
            continue;
        if (std::find(valid_operations.begin(), valid_operations.end(), *it) != valid_operations.end()) {
            mhs += *it;
            break;
        }
        lhs += *it;
    }
    for (; it != in.end(); it++) {
        if (!isalnum(*it))
            continue;
        rhs += *it;
    }

    InputData data{};
    try {
        data.lhs = std::stod(lhs);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        data.rhs = std::stod(rhs);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
    data.operation = mhs[0];

    return data;
    // Input: 5 + 5 -> operacja dodawania dwóch liczb 5 i 5 -> output: 10.
    // Input: 5 ^ 2 -> operacje potęgowania -> output 25.
    // Input: 125 $ 3 -> operacja pierwiastka (sqrt za długie), pierwiastek sześcienny z 125 -> output: 5.
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

    InputData parsed = parse_input(input);
    *out = op[parsed.operation](parsed.lhs, parsed.rhs);
    std::cout << "Actual: " << *out << "\n";
    // Funkcje kalkulatora
    // Dodawanie, mnożenie, dzielenie, odejmowanie (+, * , / , -)
    // Modulo (%)
    // Obliczanie silni (!)
    // Podnoszenie liczby do potęgi (^)
    // Obliczanie pierwiastka ({2}lt;/code>)
    return ErrorCode::OK;
}