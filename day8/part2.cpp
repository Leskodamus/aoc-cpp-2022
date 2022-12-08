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
    size_t score = 0;
    Grid grid;

    for (auto &line : input) {
        grid.push_back({line.cbegin(), line.cend()});
    }
    assert(grid.size() > 0);

    for (size_t i = 1; i < grid.size() - 1; ++i) {
        for (size_t j = 1; j < grid.at(0).size() - 1; ++j) {
            /* left, right, top, bottom */
            size_t view[4] = {0, 0, 0, 0};
            auto curr_val = grid.at(i).at(j);
            /* left */
            for (int l = j - 1, s = 1; l >= 0; --l, ++s) {
                if (grid.at(i).at(l) >= curr_val || l == 0) {
                    view[0] = s; 
                    break;
                }
            }
            /* right */
            for (int r = j + 1, s = 1; r < grid.at(i).size(); ++r, ++s) {
                if (grid.at(i).at(r) >= curr_val || r == grid.at(i).size() - 1) {
                    view[1] = s; 
                    break;
                }
            }
            /* top */
            for (int t = i - 1, s = 1; t >= 0; --t, ++s) {
                if (grid.at(t).at(j) >= curr_val || t == 0) {
                    view[2] = s; 
                    break;
                }
            }
            /* bottom */
            for (int b = i + 1, s = 1; b < grid.size(); ++b, ++s) {
                if (grid.at(b).at(j) >= curr_val || b == grid.size() - 1) {
                    view[3] = s; 
                    break;
                }
            }

            auto tree_score = 1;
            for (const auto &v : view) {
                tree_score *= v;
            }
            score = tree_score > score ? tree_score : score;
        }
    }

    cout << "Highest scenic score: " << score << endl;
}
