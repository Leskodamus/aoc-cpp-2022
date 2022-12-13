#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

bool is_number(const char n) {
    return n >= '0' && n <= '9';
}

bool compare_pair(const string& lhs, const string& rhs) {
    int l = 0, r = 0;
    while (l < lhs.size() && r < rhs.size()) {
        if (is_number(lhs[l]) && is_number(rhs[r])) {
            int n1 = 0, n2 = 0;

            while (is_number(lhs[l]))
                n1 = n1 * 10 + (lhs[l++] - '0');
            while (is_number(rhs[r]))
                n2 = n2 * 10 + (rhs[r++] - '0');

            if (n1 == n2) continue;
            else if (n1 < n2) return true;

            break;
        } else if (lhs[l] == rhs[r]) {
            ++l;
            ++r;
        }  else if (lhs[l] == ']') {
            return true;
        }  else if (rhs[r] == ']') {
            break;
        } else if (lhs[l] == '[' || lhs[l] == ',') {
            ++l; 
        } else if (rhs[r] == '[' || rhs[r] == ',') {
            ++r; 
        }    
    }

    if (l == lhs.size()) return true;
     
    return false;
}

int main(void) {
    auto input = utils::read_file("./input");
    int idx = 0, sum = 0;

    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        if (line->empty()) continue;
        ++idx;
        if (compare_pair(*line, *(line + 1))) {
            sum += idx;
        }
        ++line;
    }

    cout << "Sum of indices in right order: " << sum << endl;
}
