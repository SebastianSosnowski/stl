#include "advancedCalculator.hpp"

struct InputData {
    double lhs = 0.0;
    double rhs = 0.0;
    char operation = ' ';
};

static bool bad_character(const std::string& in) {
    std::unordered_set<char> allowed{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                     '+', '-', '*', '/', '%', '^', '$', '!', '.', ',',
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

static std::string trim(const std::string& str) {
    auto first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    auto last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

ErrorCode parse_input(const std::string& in, InputData& data, std::size_t operator_idx) {
    data.operation = in.at(operator_idx);

    std::string lhs = trim(in.substr(0, operator_idx));
    std::string rhs = trim(in.substr(operator_idx + 1));

    size_t pos;

    // parsowanie lhs
    try {
        data.lhs = std::stod(lhs, &pos);
        if (pos != lhs.size()) {
            return ErrorCode::BadFormat;
        }
    } catch (...) {
        return ErrorCode::BadFormat;
    }

    // parsowanie rhs
    if (data.operation == '!') {
        if (!rhs.empty()) {
            return ErrorCode::BadFormat;  // np. "5! 3"
        }
    } else {
        // operator wymaga rhs
        if (rhs.empty())
            return ErrorCode::BadFormat;
        try {
            data.rhs = std::stod(rhs, &pos);
            if (pos != rhs.size()) {
                // sprawdzamy, czy pierwszym znakiem reszty nie jest minus dla liczby ujemnej
                if (!(rhs[0] == '-' && pos == 1)) {
                    return ErrorCode::BadFormat;
                }
            }
        } catch (...) {
            return ErrorCode::BadFormat;
        }
    }

    return ErrorCode::OK;
}

static bool divide_by_zero(const InputData& data) {
    if (data.operation != '/') {
        return false;
    }
    if (data.rhs == 0.0) {
        return true;
    }
    return false;
}
static bool root_of_negative_number(const InputData& data) {
    if (data.operation != '$') {
        return false;
    }
    if (data.lhs < 0.0) {
        return true;
    }
    return false;
}

static bool module_of_non_integer_value(const InputData& data) {
    if (data.operation != '%') {
        return false;
    }
    if (std::trunc(data.lhs) != data.lhs || std::trunc(data.rhs) != data.rhs) {
        return true;
    }
    return false;
}

double factorial(double n) {
    // sprawdzamy, czy liczba jest całkowita
    bool is_integer = std::floor(n) == n;

    if (n < 0) {
        // ujemne liczby: bierzemy wartość bezwzględną i obliczamy silnię „dodatniej wersji”
        double positive_result;
        if (is_integer) {
            // ujemne całkowite: normalna silnia z abs(n)
            positive_result = 1.0;
            for (int i = 1; i <= static_cast<int>(std::abs(n)); ++i) {
                positive_result *= i;
            }
        } else {
            // ujemne floaty: gamma z abs(n)
            positive_result = std::tgamma(std::abs(n) + 1.0);
        }
        // przywracamy znak liczby
        return -positive_result;
    } else {
        // dodatnie liczby (int i float): gamma
        return std::tgamma(n + 1.0);
    }
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
        {'!', [](const auto& n, double) { return factorial(n); }},
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
    if (divide_by_zero(parsed)) {
        return ErrorCode::DivideBy0;
    }
    if (root_of_negative_number(parsed)) {
        return ErrorCode::SqrtOfNegativeNumber;
    }
    if (module_of_non_integer_value(parsed)) {
        return ErrorCode::ModuleOfNonIntegerValue;
    }
    *out = op[parsed.operation](parsed.lhs, parsed.rhs);
    return result;
}