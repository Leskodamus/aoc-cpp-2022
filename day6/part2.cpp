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
    size_t somm_size = 14;    /* start-of-message marker */

    for (auto line : input) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (i + somm_size < line.size() && 
                set<char>{
                    line.begin() + i, line.begin() + i + somm_size
                }.size() == somm_size) 
            {
                idx = i + somm_size;    
                goto finish;
            }
        }
    }
    finish:
    cout << "Index of first start-of-message marker: " << idx << '\n';
}
