#include <iostream>
#include <string>
#include <fstream>

bool isSymbol (char c) {
    return !std::isalpha(c) && !std::isdigit(c) && c != '.';
}

int main() {

    std::ifstream file("Inputs/thirdOfDecember.txt");

    int array[140][140];
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            array[i][j] = 0;
        };
    };
    int row = 0;
    // int column = 1;


    if (file.is_open()) {
        std::string line;
        while(std::getline(file, line)) {
            if (row == 0 || row == 139) {
                row += 1;
                continue;
            }
            for (int i = 1; i < 139; i++) {
                if (isSymbol(line[i])) {
                    array[row][i] = 1;
                    array[row][i+1] = 1;
                    array[row][i-1] = 1;

                    array[row+1][i] = 1;
                    array[row+1][i+1] = 1;
                    array[row+1][i-1] = 1;

                    array[row-1][i] = 1;
                    array[row-1][i+1] = 1;
                    array[row-1][i-1] = 1;
                };
                // column += 1;
            };
            // column = 1;
            row += 1;   
        };
        file.close();
    } else {
        std::cout << "File not found \n";
        return 1;
    };

    std::ifstream file2("Inputs/thirdOfDecember.txt");

    if (file2.is_open()) {

        int sum = 0;
        int number = 0;
        int row = 0;
        std::string stringvalue = "";
        bool usable = false;

        std::string line;
        
        while(std::getline(file2,line)) {
            number = 0;
            usable = false;
            stringvalue = "";
            for (int i = 0; i < 140; i++) {
                if (i == 139) {
                    if (usable) {
                        stringvalue += line[i];
                        number = std::stoi(stringvalue);
                        sum += number;
                    };
                    usable = false;
                    stringvalue = "";

                } else if (std::isdigit(line[i])){
                    stringvalue += line[i];
                    if (array[row][i] == 1) {
                        usable = true;
                    };
                } else {
                    if (usable) {
                        number = std::stoi(stringvalue);
                        sum += number;
                    };
                    usable = false;
                    stringvalue = "";
                };
            };
            row += 1;

        };
        std::cout << "The sum of the numbers is: " << sum << "\n";
    };

    return 0;
}