#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>

class desertMap {
    private: std::unordered_map<std::string, std::pair<std::string,std::string>> map;
    private: std::string instructions;
    private: int stepsbase;

    public: desertMap(std::string inputfile) {
        std::ifstream file(inputfile);
        std::string line;

        if (!file.is_open()) {
            std::cout << "File not found" << "\n";
        }

        std::getline(file, line);
        this->instructions = line;
        this->stepsbase = line.length();
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::string key = line.substr(0, 3);
            std::string left = line.substr(7, 3);
            std::string right = line.substr(12, 3);
            this->map[key] = std::make_pair(left, right);
        }
        file.close();
    };

    public: int solveMapPart1() {
        std::string current = "AAA";
        std::string goal = "ZZZ";

        int steps = 0;
        
        while ((current != goal) || (steps % this->stepsbase != 0)) {
            char direction = this->instructions[steps % this->stepsbase];
            std::pair<std::string, std::string> pair = this->map[current];
            if (direction == 'L') {
                current = pair.first;
            } else {
                current = pair.second;
            }
            steps++;
        }
        return steps;
    }

    public: long long solveMapPart2() {
        std::vector<std::string> current;
        char goal = 'Z';
        int keywords = 0;
        int output = 1;

        for (auto kv: this->map) {
            char letter = kv.first[2];
            if (letter == 'A') {
                current.push_back(kv.first);
            }
        };
        // std::cout << keywords << "\n";
        std::vector<int> laps;
        bool reachedGoal = true;
        // while (!reachedGoal) {

            // std::vector<std::string> newCurrent;

            for (std::string start : current) {
                int steps = 0;
                reachedGoal = true; 
                while (reachedGoal) {
                for (int i = 0; i<this->stepsbase;i++) {
                    char direction = this->instructions[i];
                    std::pair<std::string, std::string> pair = this->map[start];
                    if (direction == 'L') {
                        start = pair.first;
                    } else {
                        start = pair.second;
                    };
                    steps++;}
                
                if (start[2] == goal) {
                    reachedGoal = false;
                    laps.push_back(steps);
                };
                
                }
            }
        for (int i = 0; i<laps.size();i++) {
            output *= laps[i];
        }
        return lcm_vector(laps);
        // 13 740 108 158 591;
        // 13 740 108 158 591;
        // 101322986;
        // 68 157 968 316 532 458 0
        
    };


    private: long long lcm_vector(const std::vector<int>& numbers) {
        long long result = numbers[0];
        for (int i = 1; i < numbers.size(); i++) {
            result = std::lcm(result, static_cast<long long>(numbers[i]));
        }
        return result;
    };

};





int main() {
    std::string inputfile = "input.txt";
    desertMap map(inputfile);
    std::cout << map.solveMapPart1() << "\n";
    std::cout << "Part 2: " << map.solveMapPart2() << "\n";
    return 0;
}