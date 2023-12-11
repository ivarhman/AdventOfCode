#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class hand {
    private: std::string cards;
    private: int bet;
    private: std::string score;
    private: int rank;

    public: hand(std::string cards, int bet) {
        this->cards = cards;
        this->bet = bet;
        this->score = getscore();
    };

    private: std::string getscore() {
        std::string prevcards = "";
        std::vector<int> scores;
        std::string scorestring = "";

        for (char card : this->cards) {
            if (isdigit(card)) {
                scorestring = scorestring + "0" + char(card);
            } else {
                switch (card) {
                    case 'T': scorestring += "10";break;
                    case 'J': scorestring += "11";break;
                    case 'Q': scorestring += "12";break;
                    case 'K': scorestring += "13";break;
                    case 'A': scorestring += "14";break;
                }
            }

            if (prevcards.find(card) == std::string::npos || prevcards == "") {
                prevcards += card;
            } else { continue;}

            auto matches = std::count(this->cards.begin(), this->cards.end(), card);
            if (matches == 1) {
                continue;
            }
            scores.push_back(matches);
            // std::cout << matches << "\n";
            // std::cout << "find : " << this->cards.find(card) << "\tCard: " << card << "\thand : " << this->cards << "\n";
        
        }
        if (scores.size() == 0) {
            scores.push_back(0);
        };

        std::sort(scores.begin(), scores.end());
        std::cout << "scores: " << scores[0] << "\n";
        switch (scores[0]) {
            case 5: scorestring.insert(0, "7");break;
            case 4: scorestring.insert(0, "6");break;
            case 3:
                if (scores.size() == 2) {
                    scorestring.insert(0, "5");break;
                } else {
                    scorestring.insert(0, "4");break;
                }
            case 2: scorestring.insert(0,"3");break;
            case 1: scorestring.insert(0,"2");break;
            default: scorestring.insert(0,"1");break;
        }
        return scorestring;
    }

    public: void print() {
        std::cout << "Cards: " <<  this->cards << "\t";
        std::cout << "Score: " << this->score << "\t";
        std::cout << "Bet: " << this->bet << "\n";
    }

};



int part1(std::string inputfile) {
    int output = 0;

    std::fstream file(inputfile);
    std::string line;
    std::vector<std::string> hands1;
    std::vector<int> bet;
    std::vector<hand> hands;

    if (!file.is_open()) {
        std::cout << "File not found\n";
        return 0;
    }

    while (std::getline(file, line)) {
        hands.push_back(hand(line.substr(0,5), std::stoi(line.substr(6, line.size() - 1))));
        hands1.push_back(line.substr(0,5));
        bet.push_back(std::stoi(line.substr(6, line.size() - 1)));
    }

    file.close();

    // for (std::string hand : hands) {
    //     std::cout << hand << "\n";
    // }
    for (int i = 0; i < hands.size(); i++) {
        hands[i].print();
    }

    return output;
};

int main() {
    std::cout << "Part 1: \n" << part1("example.txt") << "\n";
    // std::cout << "Part 2: " << part2("input.txt") << "\n";
    return 0;
};