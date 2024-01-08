#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class mirrors {
    private: std::vector<std::vector<bool>> mirrorlines;


    public:  mirrors(std::vector<std::string> rawLines){
        for (std::string line : rawLines) {
            std::vector<bool> mirrorline;
            for (char c : line) {
                switch (c) {
                    case '#': mirrorline.push_back(true); break;
                    case '.': mirrorline.push_back(false); break;
                    default: throw std::invalid_argument("Invalid character in input"); break;
                }
            this->mirrorlines.push_back(mirrorline);
            }
        }

    }

};

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> rawLines;
    while (std::getline(file, line)) {
        rawLines.push_back(line);
        if (line == "") {std::cout << "Empty line" << std::endl;};
    }
    // mirrors m(rawLines);
    return 0;

}