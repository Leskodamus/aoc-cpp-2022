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
    long max = 0;

    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        if (line->empty() || line + 1 == input.cend()) {
           max = tmp > max ? tmp : max;
           tmp = 0;
        } else {
            tmp += stol(*line);
        }
    }
    
    cout << "Max calories: " << max << endl;
}
