#include <cassert>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

using Grid = vector<vector<char>>;

int main(void) {
    auto input = utils::read_file("./input");
    size_t res = 0;
    Grid grid;

    for (auto &line : input) {
        grid.push_back({line.cbegin(), line.cend()});
    }
    assert(grid.size() > 0);

    /* All outer trees are visible, -8 for corners */
    res = grid.size() * 2 + grid.at(0).size() * 2 - 4;

    for (size_t i = 1; i < grid.size() - 1; ++i) {
        for (size_t j = 1; j < grid.at(0).size() - 1; ++j) {
            /* left, right, top, bottom */
            bool is_visible[4] = {true, true, true, true};
            auto curr_val = grid.at(i).at(j);
            /* left */
            for (int l = j - 1; l >= 0; --l) {
                if (grid.at(i).at(l) >= curr_val) {
                    is_visible[0] = false; 
                    break;
                }
            }
            /* right */
            for (int r = j + 1; r < grid.at(i).size(); ++r) {
                if (grid.at(i).at(r) >= curr_val) {
                    is_visible[1] = false; 
                    break;
                }
            }
            /* top */
            for (int t = i - 1; t >= 0; --t) {
                if (grid.at(t).at(j) >= curr_val) {
                    is_visible[2] = false; 
                    break;
                }
            }
            /* bottom */
            for (int b = i + 1; b < grid.size(); ++b) {
                if (grid.at(b).at(j) >= curr_val) {
                    is_visible[3] = false; 
                    break;
                }
            }

            for (const auto &v : is_visible) {
                if (v == true) {
                    ++res;
                    break;
                }
            }
        }
    }

    cout << "Number of trees visible from outside: " << res << endl;
}
