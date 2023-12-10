#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<int> mapToNewPoint(std::vector<std::vector<int>> map, std::vector<int> seeds) {
    int output = 0;

    std::vector<int> newSeeds;

    for (int seed: seeds) {
        for (const auto& row : map) {
            int destinaton = row[0];
            int source = row[1];
            int range = row[2];

            if (seed >= source && seed < source + range) {
                output = seed - source +  destinaton;
                newSeeds.push_back(output);
            };
        };
        newSeeds.push_back(seed);
    };
    return newSeeds;
}

std::vector<int> extractNumbers(const std::string& str) {
    std::stringstream ss(str);
    int num;
    std::vector<int> numbers;
    while (ss >> num) {
        numbers.push_back(num);
    };
    return numbers;
}

int part1() {

    int output = 0;

    std::fstream file("input.txt");

    std::vector<int> seeds;

    if (file.is_open()) {
        
        for (std::string line; std::getline(file, line);) {
            if (line[5]== ":") {
                seeds = extractNumbers(line);
            }
            if (line == "") {
                std::cout << "Empty line" << "\n";
            }
        }

        file.close();
    } else {
        std::cout << "File not found" << "\n";
    }


    return output;
}


int main() {
    part1();
}