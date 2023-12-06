#include <fstream>
#include <string>
#include <iostream>

int main () {
    std::ifstream file("Inputs/secondofDecember.txt");
    int sum = 0;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line.find(";") << "\n";
        };
    } else {
        std::cout << "File Not Found" << "\n";
    };

    std::cout << sum << "\n";


    return 0;
};