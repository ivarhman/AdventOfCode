#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_map>

struct point {
    double row, column;
    point(double row, double column) : row(row), column(column) {};
};

class snakeMap {
    private: std::vector<std::string> map;
    private: std::vector<int> position;
    private: std::vector<std::vector<int>> trail;


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

    private: std::vector<int> findStartdirection() {
        std::vector<int> direction;
        std::vector<std::vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        std::unordered_map<char, std::vector<std::vector<int>>> validDirections= {
            {'F', {{-1,0}, {0,-1}}},
            {'J', {{1,0}, {0,-1}}},
            {'7', {{-1,0}, {0,-1}}},
            {'L', {{1,0}, {0,1}}},
            {'|', {{-1,0}, {1,0}}},
            {'-', {{0,-1}, {0,1}}}
        };
        std::vector<int> position = this->position;
        std::set<char> validPositions = {'F', 'J', '7', 'L','|', '-'};

        for (int i = 0; i < 4; i++){
            position = {this-> position[0] + directions[i][0], this->position[1] + directions[i][1]};
            auto findChar = validPositions.find(this->map[position[0]][position[1]]);
            if (findChar == validPositions.end()) {
                continue;
            }
            char validChar = *findChar;
            auto vectors = validDirections[validChar];
            if (vectors[0] == directions[i] || vectors[1] == directions[i]) {
                return directions[i];
            }

        }
        return direction;
    }


    public: int solveMappart1 () {
        float steps = 1;
        std::vector<int> direction;
        std::vector<int> position = this->position;


        std::vector<std::vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        direction = findStartdirection();
        position[0] += direction[0];
        position[1] += direction[1];
        this->trail.push_back(position);
        while (true) {
        switch (this->map[position[0]][position[1]]) {
            case 'F':
                if (direction[0] == -1) {
                    direction = directions[0];
                } else {
                    direction = directions[1];
                }
                break;
            case 'J':
                if (direction[0] == 0) {
                    direction = directions[3];
                } else {
                    direction = directions[2];
                }
                break;
            case '7':
                if (direction[0] == -1) {
                    direction = directions[2];
                } else {
                    direction = directions[1];
                }
                break;
            case 'L':
                if(direction[0] == 1) {
                    direction = directions[0];
                } else {
                    direction = directions[3];
                }
                break;
                case '|': break;
                case '-': break;
            default:
                std::cerr << "Error: Invalid character in map\n";
                break;}
            position[0] += direction[0];
            position[1] += direction[1];
            this->trail.push_back(position);
            steps ++;

            if (position == this->position) {
                return std::ceil((steps-1)/2);
            };
    };
    };

    public: int solveMapPart2 () {
        int pointsInside = 0;
        
        std::vector<std::vector<int>> ploygon = this->trail;

        for (int row = 0; row < this->map.size(); row++) {
            for (int column = 0; column < this->map[row].length(); column++) {
                if (this->map[row][column] == 'S') {
                    continue;
                }
                if (std::find(this->trail.begin(), this->trail.end(), std::vector<int> {row, column}) != this->trail.end()) {
                    continue;
                }
                std::vector<int> point = {row, column};
                std::cout <<"row : " << row << "\tColumn:" << point[1] << "\n";
                if (this->isInPolygon(point, ploygon)) {
                    pointsInside++;
                }
            }
        }
        std::cout << pointsInside << "\n";
        return pointsInside;
    }

    private: bool isInPolygon(std::vector<int> point, std::vector<std::vector<int>> polygon) {
        int i, j, nvert = polygon.size();
        bool c = false;

        for (i = 0, j = nvert - 1; i < nvert; j = i++) {
            if ( ((polygon[i][1] > point[1]) != (polygon[j][1] > point[1])) &&
            (point[0] < (polygon[j][0] - polygon[i][0]) * (point[1] - polygon[i][1]) / (polygon[j][1] - polygon[i][1]) + polygon[i][0]) ) {
                c = !c;
            }
        }
        return c;
    }
};



int main() {

    std::string inputfile = "input.txt";
    snakeMap playSnakes(inputfile);

    std::cout << playSnakes.solveMappart1() << "\n";
    playSnakes.solveMapPart2();


    return 0;
};