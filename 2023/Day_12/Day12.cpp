#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <string>

class spring {
    private: std::string rawLine;
    private: std::vector<int> springs;
    private: std::vector<int> instructions;
    private: int combinations = -1;

    public: spring(const std::string& rawLine) {
        this->rawLine = rawLine;
        std::string tempval = "";
        int temp;
        for (char c : rawLine) {
            switch (c) {
                case '.': this->springs.push_back(0); break;
                case '#': this->springs.push_back(2); break;
                case '?': this->springs.push_back(1); break;
                case ' ': break;
                case ',': 
                    temp = std::stoi(tempval);
                    this->instructions.push_back(temp);
                    tempval = ""; 
                    break;
                default: 
                    tempval += c; 
                    break;
            }
        }
        temp = std::stoi(tempval);
        this->instructions.push_back(temp);
    }



    private: void findCombinations() {
        int combination = 0;

        // Walk the springs and find possible combinations

        // if the spring is a 0, its a faulty spring and cannot be used
        // if the spring is a 2, its a solid spring and can be used
        // if the spring is a 1, its conditions is unknow, so we need to check the instructions
        /*
            Need to know if the location is possible.


            First find which are locked?
                start at each end and find locked ones?
                
        */

    }

    public: void print() {
        std::cout << "Springs: \t";
        for (int i = 0; i < this->springs.size(); i++) {
            std::cout << this->springs[i] << " ";
        }
        std::cout << "\nInstructions: \t";
        for (int i = 0; i < this->instructions.size(); i++) {
            std::cout << this->instructions[i] << "\t";
        }
        std::cout << "\n";
    
    }


};

int main() {
    std::fstream file("example.txt");
    std::string line;
    std::vector<spring> springs;

    if (!file.is_open()) {
        std::cerr << "File not found!";
    }

    while (std::getline(file, line)) {
        springs.push_back(spring(line));
    }
    file.close();


    for (int i = 0; i < springs.size(); i++) {
        springs[i].print();
    }

    return 0;
}