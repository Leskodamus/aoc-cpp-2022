#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

int main(void) {
    auto input = utils::read_file("./input");
    int res = 0;

    for (auto line : input) {
        auto pair_delim = line.find_first_of(',');
        auto range_delim_fst = line.find_first_of('-');
        auto range_delim_snd = line.find_last_of('-');

        auto fst_range = make_pair(
                stoul(line.substr(0, range_delim_fst)),
                stoul(line.substr(range_delim_fst + 1, pair_delim - range_delim_fst - 1))
        );

        auto snd_range = make_pair(
                stoul(line.substr(pair_delim + 1, range_delim_snd - pair_delim - 1)),
                stoul(line.substr(range_delim_snd + 1))
        );

        if ((fst_range.first >= snd_range.first &&
            fst_range.second <= snd_range.second) || 
            snd_range.first >= fst_range.first && 
            snd_range.second <= fst_range.second)
        {
            ++res;
        }
    }

    cout << "Number of assignment pairs fully containing the other: " << res << '\n';
}
