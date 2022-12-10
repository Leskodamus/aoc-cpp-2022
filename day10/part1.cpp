#include <cstddef>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

using Register = int;

void get_signal_strength(const Register &X, const size_t cycles, int &sum) {
    if (cycles % 40 == 20) {
        sum += cycles * X;
    }
}

int main(void) {
    auto input = utils::read_file("./input");
    Register X = 1;
    size_t cycles = 0;
    int sum = 0;

    for (const auto &line : input) {
        auto delim = line.find_first_of(' ');
        string instruction = line.substr(0, delim);

        if (instruction == "noop") {
            ++cycles;
            get_signal_strength(X, cycles, sum);
        } else if (instruction == "addx") {
            int number = 0;

            if (line[delim + 1] == '-') {
                number = stoi(line.substr(delim + 2)) * (-1);
            } else {
                number = stoi(line.substr(delim + 1));
            }

            for (size_t i = 1; i <= 2; ++i) {
                ++cycles;
                get_signal_strength(X, cycles, sum);
                if (i == 2)
                    X += number;
            }
        }
    }

    cout << "Sum of signal strengths: " << sum << endl;
}
