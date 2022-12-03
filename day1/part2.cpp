#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

int main(void) {
    auto input = utils::read_file("./input");
    long tmp = 0;
    long max[3] = {0};

    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        if (line->empty() || line + 1 == input.cend()) {
            for (size_t i = 0; i < sizeof(max); ++i) {
                if (tmp > max[i]) {
                    max[i] ^= tmp;
                    tmp ^= max[i];
                    max[i] ^= tmp;
                }
            }
            tmp = 0;
        } else {
            tmp += stol(*line);
        }
    }

    cout << "Max calories: " << max[0] + max[1] + max[2] << endl;
}
