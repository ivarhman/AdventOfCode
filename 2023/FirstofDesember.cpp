#include <iostream>
#include <fstream>
#include <istream>
#include <cctype>
#include <vector>
#include <regex>

int main() {
    std::ifstream file("Inputs/FirstofDesember.txt");
//    std::ofstream fileo("Outputs/FirstofDesember.txt");
    
    std::string line;
    std::string output;
    std::string temp;

    std::vector<std::pair<std::regex, std::string>> regexes = {
        {std::regex ("oneight"), "18"},
        {std::regex ("twone"), "21"},
        {std::regex ("threeight"), "38"},
        {std::regex ("fiveight"), "58"},
        {std::regex ("sevenine"), "79"},
        {std::regex ("eightwo"), "82"},
        {std::regex ("eightree"), "83"},
        {std::regex ("nineight"), "98"},

        {std::regex("one"),"1"},
        {std::regex("two"),"2"},
        {std::regex("three"),"3"},
        {std::regex("four"),"4"},
        {std::regex("five"),"5"},
        {std::regex("six"),"6"},
        {std::regex("seven"),"7"},
        {std::regex("eight"),"8"},
        {std::regex("nine"),"9"},
    };

    int calibrationValue = 0;
    std::smatch match;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            for (const auto& pair : regexes) {
                auto regex = pair.first;
                auto replacement = pair.second;
                line = std::regex_replace(line, regex, replacement);
            }
            for (char c : line) {
                if (std::isdigit(c)) {
                    temp += c;
                }

            }
            calibrationValue += (int(temp[0])-'0')*10 + (int(temp[temp.size() - 1])-'0');
            temp = "";
        }
    } else {
        std::cout << "File Not Found" << "\n";
    };
    std::cout << calibrationValue << "\n";
    file.close();

    return 0;
}