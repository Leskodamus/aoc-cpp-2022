#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include "../utils/utils.hpp"

using namespace std;

int main(void) {
    auto input = utils::read_file("./input");
    size_t idx = 0;
    size_t sopm_size = 4;    /* start-of-packet marker */

    for (auto line : input) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (set<char>{
                    line.begin() + i, line.begin() + i + sopm_size
                }.size() == sopm_size) 
            {
                idx = i + sopm_size;    
                goto finish;
            }
        }
    }
    finish:
    cout << "Index of first start-of-packet marker: " << idx << '\n';
}
