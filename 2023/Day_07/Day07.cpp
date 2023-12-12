#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>

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

    public: void setRank(int rankinorder) {
        this->rank = rankinorder;
    };

    public: std::string getscore() {
        std::string prevcards = "";
        std::vector<int> scores;
        std::string scorestring = "";
        std::string highcard = "";
        int jokers = 0;

        for (char card : this->cards) {
            if (isdigit(card)) {
                scorestring = scorestring + "0" + char(card);
            } else {
                switch (card) {
                    case 'T': scorestring += "10";break;
                    case 'J': scorestring += "01"; jokers++;continue; // Change to 11 for part 2
                    case 'Q': scorestring += "12";break;
                    case 'K': scorestring += "13";break;
                    case 'A': scorestring += "14";break;
                }
            }

            if (highcard == "" || (stoi(scorestring.substr(scorestring.size() - 2, 2)) > stoi(highcard))) {
                highcard = scorestring.substr(scorestring.size() - 2, 2);
            }

            if (prevcards.find(card) == std::string::npos || prevcards == "") {
                prevcards += card;
            } else { continue;}

            auto matches = std::count(this->cards.begin(), this->cards.end(), card);
            if (matches == 1) {
                continue;
            }
            scores.push_back(matches);        
        }
        if (scores.size() == 0) {
            scores.push_back(1);
        };

        std::sort(scores.begin(), scores.end());
        scores[scores.size() - 1] += jokers;
        if (jokers == 5) { 
            score[0] = 5;
        }
        if (scores[0] > 5) {
            scores[0] = 5;
        }

        switch (scores[0]) {
            case 5: scorestring.insert(0, "700");break;
            case 4: scorestring.insert(0, "600");break;
            case 3: scorestring.insert(0, "400");break;
            case 2:
                if (scores.size() == 2 && scores[1] == 3) {
                    scorestring.insert(0, "500");
                } else if (scores.size() == 2) {
                    scorestring.insert(0,"300");
                } else {
                scorestring.insert(0, "200");
                }; break;
            case 1:
                scorestring.insert(0,highcard);
                scorestring.insert(0,"1");break;
            default: scorestring.insert(0,"000");
            std::cerr << "Error: " << scores[0] << "\n";break;
        }
        return scorestring;
    };

    public: void print() {
        std::cout << "Cards: " <<  this->cards << "\t";
        std::cout << "Score: " << this->score << "\t";
        std::cout << std::stoll(this->score) << "\t";
        std::cout << "Rank: " << this->rank << "  \t";
        std::cout << "Bet: " << this->bet << "\n";
    };

    public: std::string getScore() {
        return this->score;
    };

    public: int getBet() {
        return this->bet;
    };
    public: int getRank() {
        return this->rank;
    };

};

class camelCards {
    private: std::vector<hand> hands;

    public: camelCards (const std::string inputfile) {
        std::fstream file(inputfile);
        std::string line;

        if (!file.is_open()) {
            std::cout << "File not found\n";
        }

        while (std::getline(file, line)) {
            this->hands.push_back(hand(line.substr(0,5), std::stoi(line.substr(6, line.size() - 1))));
        }

        file.close();
        rankScores();
    };

    public: void rankScores() {
        std::vector<std::string> scores;
        
        for (int i = 0; i < this->hands.size(); i++) {
            scores.push_back(this->hands[i].getScore());
        };
        std::vector<std::string> rawscore = scores;
        std::vector<int>prevranks;
        std::sort(scores.begin(),scores.end()); // remove for part 1

        for (int i = 0; i < scores.size(); i++) {
            for (int j = 0; j < rawscore.size(); j++) {
                if (scores[i] == rawscore[j]) {
                    this->hands[j].setRank(i+1);
                    prevranks.push_back(i+1);
                    break;
                }
            }
        }
        std::set<int> unique_numbers(prevranks.begin(), prevranks.end());
        if (unique_numbers.size() != prevranks.size()) {
            std::cout << "Error: Duplicate ranks\n";
        }

    };

    public: int getpart1() {
        int output = 0;

        for (int i = 0; i<this->hands.size(); i++) {
            output += (this->hands[i].getBet() * this->hands[i].getRank());
        }
        return output;
    }

    public: void print(){
        for (int i = 0;i < this->hands.size();i++) {
            this->hands[i].print();
        };
    };
};

int part1(const std::string inputfile) {
    camelCards game(inputfile);
    game.print();
    return game.getpart1();
};

int main() {
    camelCards game("input.txt");
    game.print();
    std::cout << "Part 1: \n" << game.getpart1() << "\n";
    // std::cout << "Part 2: " << part2("input.txt") << "\n";
    return 0;
};