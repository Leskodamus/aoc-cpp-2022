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
    string group[3];
    int gc = 0;
    int sum = 0;

    while (getline(ifs, line)) {
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
