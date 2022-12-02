#include <cstddef>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <utility>

using namespace std;

enum Points {
    Lose = 0,
    Draw = 3,
    Win = 6,
};

enum Shape {
    Rock = 1,
    Paper = 2,
    Scissors = 3,
};

int main(void) {
    ifstream ifs("./input", ios_base::in);
    if (!ifs.is_open()) {
        cerr << "Failed to open input file.\n";
        return EXIT_FAILURE;
    }
    
    size_t score = 0;
    string line;
    pair<Shape, Shape> round;

    while (getline(ifs, line)) {
        auto delim = line.find(' ');
        auto guide = make_pair(
            line.substr(0, delim),
            line.substr(delim+1)
        );

        if (guide.first == "A") {
            round.first = Rock; 
        } else if (guide.first == "B") {
            round.first = Paper;
        } else if (guide.first == "C") {
            round.first = Scissors;
        } else {
            cerr << "Wrong input on the left.\n";
            return EXIT_FAILURE;
        }

        if (guide.second == "X") {
            round.second = Rock; 
        } else if (guide.second == "Y") {
            round.second = Paper;
        } else if (guide.second == "Z") {
            round.second = Scissors;
        } else {
            cerr << "Wrong input on the right.\n";
            return EXIT_FAILURE;
        }

        if (round.first == round.second) {
            score += Draw + round.first; 
        } else if (round.first == Rock && round.second == Paper) {
            score += Win + Paper;
        } else if (round.first == Rock && round.second == Scissors) {
            score += Lose + Scissors;
        } else if (round.first == Paper && round.second == Scissors) {
            score += Win + Scissors;
        } else if (round.first == Paper && round.second == Rock) {
            score += Lose + Rock;
        } else if (round.first == Scissors && round.second == Rock) {
            score += Win + Rock;
        } else if (round.first == Scissors && round.second == Paper) {
            score += Lose + Paper;
        }
    }

    cout << "Total score: " << score << '\n';
}
