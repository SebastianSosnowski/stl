#include <vector>
#include "advancedCalculator.hpp"

int main() {
    std::vector<std::string> v{
        "43.21+11.54",
        "2 - 7",
        "2 * 3",
        "5 / 3",
        "6 % 4",
        "2 ^ 3",
        "16 $ 2",
        "4!",
        "5,1!",
        "-13!",
        "-12.4!",
        "-123 $ -1",
        "123 % 0.1",
        "13.2 + 12.3 + 13.0",
    };

    for (const auto& op : v) {
        double result = 0;
        ErrorCode err = process(op, &result);
        std::cout << "Operation: " << op << ", ErrorCode: " << static_cast<int>(err) << ", Result: " << result << "\n";
    }
    return 0;
}