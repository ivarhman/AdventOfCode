#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<int> extractNumbers(const std::string& str) {
    std::stringstream ss(str);
    int num;
    std::vector<int> numbers;

    while (ss >> num) {
        numbers.push_back(num);
    }

    return numbers;
}

int part1() {
    std::fstream file("input.txt");

    std::string winningNumbers;
    std::string ownNumbers;

    int output = 0;

    if (file.is_open()) {
        for (std::string line; std::getline(file, line);) {
            double sum = 0.5;
            winningNumbers = line.substr(10, 29);
            ownNumbers = line.substr(42, 100);
            
            std::vector<int> winningNumbersList = extractNumbers(winningNumbers);
            std::vector<int> ownNumbersList = extractNumbers(ownNumbers);
            for (int number : ownNumbersList) {
                if (std::find(winningNumbersList.begin(), winningNumbersList.end(), number) != winningNumbersList.end()) {
                    sum *= 2;
                    std::cout << "Found: " << number << "Sum: " << sum << "\n";
                }
            }
            if (sum!= 0.5) {
                output += sum;
            }

        }

    file.close();   
    } else {
        std::cerr << "File not found \n";
    }
    std::cout << output << "\n";
    return output;

}

int part2() {
    std::fstream file("input.txt");

    std::string winningNumbers;
    std::string ownNumbers;

    int output = 0;
    int array[189];
    int matches = 0;
    for (int i = 0; i < 189; i++) {
        array[i] = 1;
    }

    if (file.is_open()) {
        int row = 0;
        for (std::string line; std::getline(file, line);) {
            winningNumbers = line.substr(10, 29);
            ownNumbers = line.substr(42, 100);
            matches = 0;

            std::vector<int> winningNumbersList = extractNumbers(winningNumbers);
            std::vector<int> ownNumbersList = extractNumbers(ownNumbers);
            for (int number : ownNumbersList) {
                if (std::find(winningNumbersList.begin(), winningNumbersList.end(), number) != winningNumbersList.end()) {
                    matches += 1;
                }
            }
            for (int i = 0; i< matches; i++) {
                array[row+i+1] += array[row];
            }
            output += array[row];
        row += 1;
        }

    file.close();   
    } else {
        std::cerr << "File not found \n";
    }
    std::cout << output << "\n";
    return output;
};


int main() {
    // part1();
    part2();
    return 1;
};