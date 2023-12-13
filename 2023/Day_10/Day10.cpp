#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>


class snakeMap {
    private: std::vector<std::string> map;
    private: std::vector<int> position;


    public: snakeMap(std::string inputfile) {

        std::fstream file(inputfile);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "File not found!";
        }
        int row = 0;
        while (std::getline(file, line)) {
            this->map.push_back(line);
            int column = 0;
            for (char c : line) {
                if (c == 'S') {
                    this->position = {row, column};
                }
                column++;
            }
            row ++;
        }

        file.close();

        

    };


    public: int solveMappart1 () {
        float steps = 0;
        std::vector<int> direction;
        std::vector<int> position = this->position;


        std::vector<std::vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        direction = directions[0];

        while (true) {}

        while (true) {
        switch (this->map[position[0]][position[1]]) {
            case 'F':
                if (direction[0] == 1) {
                    direction = directions[0];
                } else {
                    direction = directions[3];
                }
                break;
            case 'J':
                if (direction[0] == 0) {
                    direction = directions[1];
                } else {
                    direction = directions[2];
                }
                break;
            case '|':
                break;
            case '-':
                break;
            default:
                std::cerr << "Error: Invalid character in map\n";
                break;}
            position[0] += direction[0];
            position[1] += direction[1];

            if (position == this->position) {
                return std::ceil(steps);
            }
    }
    };
};



int main() {

    std::string inputfile = "example.txt";
    snakeMap playSnakes(inputfile);



    return 0;
}