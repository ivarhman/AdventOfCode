#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>

std::vector<int> extractNumbers(const std::string& line) {
    std::stringstream ss(line);
    int  num;
    std::vector<int> numbers;
    while( ss >> num) {
        numbers.push_back(num);
    };
    return numbers;
}

bool isZero(const std::vector<int>& numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] != 0 ) {
            return false;
        }
    }
    return true;
}


std::vector<int> diff(const std::vector<int>& numbers) {
    std::vector<int> result;
    for (size_t i = 1; i < numbers.size(); i++) {
        result.push_back(numbers[i] - numbers[i-1]);
    };
    return result;
};

int main() {
    std::fstream file("input.txt");

    if (!file.is_open()) {
        std::cout << "File not found!\n";
        return 0;
    }
    std::string line;
    int predictions = 0;
    while (std::getline(file, line)){
        std::vector<int> history = extractNumbers(line);
        std::vector<int> prevEnds = {history[0]};


        history = diff(history);
        prevEnds.push_back(history[0]);

        bool zeroes = isZero(history);
        while (!zeroes) {
            history = diff(history);
            zeroes = isZero(history);
            prevEnds.push_back(history[0]);
        }
        
        int sum = 0;
        for (int i = prevEnds.size()-1; i > -1; i--) {
            sum = prevEnds[i] - sum;
            // std::cout << prevEnds[i] << "\n";
            // std::cout <<" " << sum << " " ;
        }
        // std::cout << sum << "\n";
        predictions += sum;
    }
    
    std::cout << predictions;

    return 0;
}