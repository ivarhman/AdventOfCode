#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

std::vector<int> extractNumbers(const std::string& line) {
    std::stringstream ss(line);
    int  num;
    std::vector<int> numbers;
    while( ss >> num) {
        numbers.push_back(num);
    };
    return numbers;
}


int part1 (std::string inputfile) {
    int output = 1;

    std::fstream file(inputfile);
    std::string line;


    if (!file.is_open()) {
        std::cout << "File not found\n";
        return 0;
    }
    std::getline(file, line);
    line = line.substr(11, line.size() - 1);
    std::vector<int> times = extractNumbers(line);
    
    std::getline(file,line);
    line = line.substr(11, line.size() - 1);
    std::vector<int> distances = extractNumbers(line);

    file.close();

    for (int i = 0; i < times.size(); i++) {
        std::cout << "Race Nr: \t" << i+1 << "\n";
        int numWinning = 0;
        for (int j = 0; j < times[i]; j++) {
            int distance = j * (times[i] - j);
            if (distance > distances[i]) {
                numWinning++;
            }
        }
        std::cout << "Winning: \t" << numWinning << "\n";
        output *= numWinning;
    }


    return output;
}


int part2 (std::string inputfile) {
    int output = 0;

    std::fstream file(inputfile);
    std::string line;

    std::string stringvalue = "";

    if (!file.is_open()) {
        std::cout << "File not found\n";
        return 0;
    }
    std::getline(file, line);
    line = line.substr(11, line.size() - 1);
    for (char c : line) {
        if (std::isdigit(c)) {
            stringvalue += c;
         }
    }
    long long time = std::stoi(stringvalue);
    
    std::getline(file,line);
    line = line.substr(11, line.size() - 1);
    stringvalue = "";
    for (char c : line) {
        if (std::isdigit(c)) {
            stringvalue += c;
         }
    }
    long long distances = std::stoll(stringvalue);

    file.close();


    for (int j = 0; j < time; j++) {
        long long distance = j * (time - j);
        if (distance > distances) {
            output++;
        }
    }
    return output;
}

int main() {
    std::cout << "Part 1:\t" << part1("input.txt") << "\n";
    std::cout << "Part 2:\t" << part2("input.txt") << "\n";
    return 0;
}
