#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int main(void) {
    ifstream ifs("./input", ios_base::in);
    if (!ifs.is_open()) {
        cerr << "Failed to open input file.\n";
        return EXIT_FAILURE;
    }
    
    string line;
    int sum = 0;

    while (getline(ifs, line)) {
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

    cout << "Total score: " << sum << '\n';
}
