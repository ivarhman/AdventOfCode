#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

struct star {
    long long  row, column;
    star (long long row, long long column) : row(row), column(column) {};
}; 



int main() {
    std::string inputfile = "input.txt";

    std::fstream file(inputfile);

    std::vector<star> stars;
    std::string line;

    std::vector<int> missingColumns;
    std::vector<int> missingRows;

    for (int i = 0; i < 140; i++) {
        missingColumns.push_back(i);
    }


    int row = 0;

    if (!file.is_open()) {
        std::cout << "File not found!\n";
        return 0;
    }

    while(std::getline(file,line)) {
        int column  = 0;
        bool noStars = true;
        for (char c : line) {
            if (c == '#') {
                noStars = false;
                stars.push_back(star(row, column));
                missingColumns.erase(std::remove(missingColumns.begin(), missingColumns.end(), column), missingColumns.end());
            }
            column ++;
            }
        if (noStars) {
            missingRows.push_back(row);
        }
        row++;
    }
    file.close();


    for (int i = 0; i < stars.size(); i++) {
        int value = stars[i].column;
        int count = std::count_if(missingColumns.begin(), missingColumns.end(), [value](int x) {
            return x < value;});
        stars[i].column += count*(1000000-1);

        value = stars[i].row;
        count = std::count_if(missingRows.begin(), missingRows.end(), [value](int x) {
            return x < value;});
        stars[i].row += count*(1000000-1);
        ;
    };

    long long distance;
    long long sum = 0;

    int pairs = 0;

    for (int i = 0; i < stars.size(); i++) {
        for (int l = i+1; l < stars.size(); l++) {
            long long  changerow = stars[i].row - stars[l].row;
            long long changecol = stars[i].column - stars[l].column;
            distance = std::abs(stars[i].row - stars[l].row) + std::abs(stars[i].column - stars[l].column);
            sum += distance;
            pairs++;
            // std::cout << i+1 << " " << l+1 << " " << distance << "\t" << "Row: " <<stars[i].row << " " << stars[l].row << "\t" << "Col: " << stars[i].column << " " << stars[l].column << "\n";
        }
    }

    for (int i = 0; i < stars.size(); i++) {
        std::cout << stars[i].row << " " << stars[i].column << "\n";
    }

    std::cout << "Pairs: " << pairs << "\n";
    std::cout << "Sum :"   << sum << "\n";

    return -1;
}