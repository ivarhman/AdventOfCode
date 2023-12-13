#include <iostream>
#include <vector>
#include <numeric>

class LCMCalculator {
    public: long long lcm_vector(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            return 0; // Handle empty vector case
        }

        long long result = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) {
            result = std::lcm(result, static_cast<long long>(numbers[i]));
        }
        return result;
    }
};

int main() {
    LCMCalculator calculator;

    std::vector<int> numbers = {13940, 11310, 16044, 20778, 18674, 17622};
    long long result = calculator.lcm_vector(numbers);

    std::cout << "LCM: " << result << std::endl;

    return 0;}