#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>

enum class ErrorCode {
    OK,
    BadCharacter,            // znak inny niż liczba
    BadFormat,               // zły format komendy np. + 5 4, powinno być 4 + 5
    DivideBy0,               // dzielenie przez 0
    SqrtOfNegativeNumber,    // pierwiastek z liczby ujemnej
    ModuleOfNonIntegerValue  // próba obliczenia % na liczbie niecałkowitej
};

ErrorCode process(std::string input, double* out);