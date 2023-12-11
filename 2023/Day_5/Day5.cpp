#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<long long> mapToNewPoint(std::vector<std::vector<long long>> map, std::vector<long long> seeds) {
    long long output = 0;
    std::vector<long long> newSeeds;
    bool seeded = false;

    for (long long seed: seeds) {
        for (const auto& row : map) {
            long long destinaton = row[0];
            long long source = row[1];
            long long range = row[2];

            if (seed >= source && seed < source + range) {
                output = seed - source +  destinaton;
                newSeeds.push_back(output);
                seeded = true;
                break;
            };
        };
        if (!seeded) {
            newSeeds.push_back(seed);
        }
        seeded = false;
    };
    return newSeeds;
}

std::vector<long long> extractNumbers(const std::string& str) {
    std::stringstream ss(str);
    long long num;
    std::vector<long long> numbers;
    while (ss >> num) {
        numbers.push_back(num);
    };
    return numbers;
}

long long part1() {

    long long output = 0;
    bool seedFound = false;
    std::vector<long long> seeds;
    std::vector<long long> originalSeeds;
    std::vector<std::vector<long long>> map;

    std::fstream file("input.txt");


    if (file.is_open()) {
        
        for (std::string line; std::getline(file, line);) {
            if (line == "") {
                if (seedFound) {
                    std::cout << "Seeds:\t" << seeds.size() << "\n";
                    seeds = mapToNewPoint(map, seeds);
                }
                map = {};
                continue;
            }

            if (isdigit(line[0])) {
                std::vector <long long> mapline = extractNumbers(line);
                map.push_back(mapline);
                continue;
            }

            if (line.find("seeds") != std::string::npos) {
                line = line.substr(7, 212);
                std::cout << "Seeds :" << line << "\n";
                seeds = extractNumbers(line);
                originalSeeds = seeds;
                seedFound = true; 
            }

        }
        if (seedFound) {
            std::cout << "Seeds:\t" << seeds.size() << "\n";
            seeds = mapToNewPoint(map, seeds);
        }

        file.close();
    } else {
        std::cout << "File not found" << "\n";
    }

    int i = 1;
    for (long long number: seeds) {
        std::cout << number << "\t" << i << "\n";
        i++;
    }
    output = std::min_element(seeds.begin(), seeds.end())[0];
    return output;
}

long long part2() {

    long long output = 0;
    bool seedFound = false;
    std::vector<long long> seeds;
    std::vector<long long> originalSeeds;
    std::vector<std::vector<long long>> map;

    std::fstream file("input.txt");


    if (file.is_open()) {
        
        for (std::string line; std::getline(file, line);) {
            if (line == "") {
                if (seedFound) {
                    seeds = mapToNewPoint(map, seeds);
                }
                map = {};
                continue;
            }

            if (isdigit(line[0])) {
                std::vector <long long> mapline = extractNumbers(line);
                map.push_back(mapline);
                continue;
            }

            if (line.find("seeds") != std::string::npos) {
                line = line.substr(7, 212);
                seeds = extractNumbers(line);
                for (int i=0; i<seeds.size(); i+=2) {
                    long long start = seeds[i];
                    long long endvalue = seeds[i+1] + seeds[i];
                    std::cout << "Start: \t" << start << "\tEnd: \t" << endvalue << "\n";
                    for (long long l = start; l < endvalue;l++) {
                        originalSeeds.push_back(l);
                    }
                }
                seeds = originalSeeds;
                //originalSeeds = seeds;
                seedFound = true; 
            }

        }
        if (seedFound) {
            seeds = mapToNewPoint(map, seeds);
        }

        file.close();
    } else {
        std::cout << "File not found" << "\n";
    }

    output = std::min_element(seeds.begin(), seeds.end())[0];
    return output;
}


int main() {
    long long part1Solution = part1();
    std::cout << "Part 1: " << part1Solution << "\n";

    long long part2Solution = part2();
    std::cout << "Part 2: " << part2Solution << "\n";
}