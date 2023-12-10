#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

int main () {
    std::ifstream file("Inputs/secondofDecember.txt");
    std::string roundstring;
    std::string token;

    int sum = 0;
    int findresults = 0;
    int id = 0;
    int comparison = 0;
    int value = 0;
    int red = 0;
    int green = 0;
    int blue = 0;

    bool possible = true;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            red = 0;
            green = 0;
            blue = 0;
            findresults = line.find(":");/*
            if (findresults == 6) {
                id = int(line[findresults-1]) - '0';
            } else if (findresults == 7){
                id = int(line[findresults-2]) - '0';
                id *= 10;
                id += int(line[findresults-1]) - '0';
            } else {
                id = 100;
            };*/
            line = line.substr(findresults + 1);

            std::stringstream ss(line);
            possible = true;
            while (std::getline(ss, token, ';')) {

                std::stringstream ssi(token);

                while (std::getline(ssi, token, ',')) {

                    value = std::stoi(token.substr(0,3));

                    if (token[token.size()-1] == 'd'){
                        comparison = 12;
                        red = std::max(red, value);
                    } else if (token[token.size()-1] == 'n')
                    {
                        comparison = 13;
                        green = std::max(green, value);
                    } else if (token[token.size()-1] == 'e')
                    {
                        comparison = 14;
                        blue = std::max(blue, value);
                    }
                    /* Break and set possible to false for the first par of the problem
                    if (value > comparison) {
                        possible = false;
                        break;
                    };
                    */
                };
                id = red * green * blue;
            };
            if (possible) {
                sum += id;
            };
            // std::cout << findresults << "\n";
            
        };
    } else {
        std::cout << "File Not Found" << "\n";
    };

    std::cout << sum << "\n";   
    return 0;
};