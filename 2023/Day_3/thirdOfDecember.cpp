#include <iostream>
#include <string>
#include <fstream>

bool isSymbol (char c) {
    return !std::isalpha(c) && !std::isdigit(c) && c != '.' && c != ' ' && c != '\n';
}

int findValues(char array[140][140] ,int Row,int column) {
    int output = 1;
    // std::cout << "Row: " << Row << " Column: " << column << "\n";

    for (int i = -1; i < 2; i++) {
        int sizeofnumber = 0;
        std::string stringvalue = "";
        bool numbers = false;
        int value = 0;
        for (int l = -1; l < 2; l++) {
            // std::cout << "Row: " << Row+i << " Column: " << column+l << "\n";
            if (std::isdigit(array[Row+i][column+l])) {
                // stringvalue += array[Row+i][column+l];
                sizeofnumber += 1;
                numbers = true;
            } else {
                if(numbers) {
                    // stringvalue = array[Row + i][column+l-1] + array[Row+i][column+l];
                    value = (int(array[Row+i][column+l-1])-'0');
                    if (std::isdigit(array[Row+i][column+l-2])) {
                        value = (int(array[Row+i][column+l-2])-'0')*10 + value;
                    };
                    if (std::isdigit(array[Row+i][column+l-3])) {

                        value = (int(array[Row+i][column+l-3])-'0')*100 + value;
                    };
                    // std::cout << array[Row+i][column+l-2] << array[Row+i][column+l-1];
                    output *= value;
                    std::cout << "\tValue1: " << value;
                    };
                // output *= std::stoi(stringvalue);
                stringvalue = "";
                numbers = false;
                sizeofnumber = 0;
            };
        };
        if (numbers) {
                // stringvalue = array[Row+i][column+2 - sizeofnumber] + array[Row + i][column +3-sizeofnumber] + array[Row+i][column +4   -sizeofnumber];
                value = (int(array[Row+i][column+2 - sizeofnumber]) - '0');
                if (std::isdigit(array[Row+i][column +3 -sizeofnumber])) {
                    value = value * 10 + int(array[Row+i][column +3   -sizeofnumber])-'0';
                }
                if (std::isdigit(array[Row+i][column +4 -sizeofnumber])){
                    value = value * 10 + int(array[Row+i][column +4   -sizeofnumber])-'0';
                }
                output *= value;
                std::cout << "\tValue2: " << value;
        };
    };
    // std::cout << "\n";
    std::cout << "\t total: " << output << "      \t Row: " << Row << "  \t Column: " << column << "\n";
    return output;
}


int main() {

    std::ifstream file("input.txt");
    std::ofstream outputfile("OutputDay3.txt");


    char inputdata [140][140];
    int row = 0;
    int sum = 0;
    int totalgears = 0;

    if (file.is_open()) {
        std::string line;
        while(std::getline(file, line)) {

            for (int i = 0; i < 140; i++) {
                inputdata[row][i] = line[i];
            };

            row += 1;
        };
        file.close();
    } else {
        std::cout << "File not found \n";
        return 1;
    };

    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            int gears = 0;
            bool continous = false;
            if (isSymbol(inputdata[i][j])) {
                char matrix [3][3] = {
                    {inputdata[i-1][j-1], inputdata[i-1][j], inputdata[i-1][j+1]},
                    {inputdata[i][j-1], inputdata[i][j], inputdata[i][j+1]},
                    {inputdata[i+1][j-1], inputdata[i+1][j], inputdata[i+1][j+1]}
                };
                for (int k = 0; k < 3; k++) {
                    continous = false;
                    for (int l = 0; l < 3; l++) {
                        if (std::isdigit(matrix[k][l])) {
                            if (continous) {
                                continue;
                            }
                            gears += 1;
                            continous = true;
                        } else {
                            continous = false;
                        };
                    };
                };
                if (gears == 2) {
                    totalgears += 1;
                    // std::cout << "Sum: " << sum << "\n";
                    sum += findValues(inputdata, i, j);
                    //std::cout << "Sum: " << sum << "\n";
                    outputfile << "1";
                } else {
                    outputfile << "0";
                };
            } else {
                outputfile << "0"; };
        };
        outputfile << "\n";
    };

    std::cout << sum << "\n";
    std::cout << totalgears << "\n";

    /*
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
    };*/

    return 0;
}