#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

int main(void) {
    auto input = utils::read_file("./input");
    int sum = 0;

    for (auto line : input) {
        auto len = line.length();
        auto mid = len / 2;
        string fst = line.substr(0, mid);
        string snd = line.substr(mid, len);
        
        set<char> found;

        for (auto left = fst.cbegin(); left != fst.cend(); ++left) {
            char c = *left;
            if (snd.find(c) == string::npos || 
                found.find(c) != found.end()) {
                continue;
            }
            found.insert(c);
            sum += (c < 97 ? c - 38 : c - 96);
        }
    }

    cout << "Sum of priorities: " << sum << '\n';
}
