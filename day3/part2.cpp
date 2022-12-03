#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

int main(void) {
    auto input = utils::read_file("./input");
    string group[3];
    int gc = 0;
    int sum = 0;

    for (auto line : input) {
        group[gc++] = line;

        if (gc == 3) {
            set<char> found;
            for (auto left = group[0].cbegin(); left != group[0].cend(); ++left) {
                char c = *left;
                if (group[1].find(c) != string::npos && 
                    group[2].find(c) != string::npos &&
                    found.find(c) == found.end()) 
                {
                    found.insert(c);
                    sum += (c < 97 ? c - 38 : c - 96);
                }
            }
            gc = 0;
        }
    }

    cout << "Sum of priorities: " << sum << '\n';
}
