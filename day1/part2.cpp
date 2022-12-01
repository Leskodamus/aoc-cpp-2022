#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
    ifstream ifs("./input", ios_base::in);
    if (!ifs.is_open()) {
        cerr << "Failed to open input file.\n";
        return EXIT_FAILURE;
    }

    string line;
    long tmp = 0;
    long max[3] = {0};

    while (getline(ifs, line)) {
        if (line.empty() || ifs.peek() == EOF) {
            for (size_t i = 0; i < sizeof(max); ++i) {
                if (tmp > max[i]) {
                    max[i] ^= tmp;
                    tmp ^= max[i];
                    max[i] ^= tmp;
                }
            }
            tmp = 0;
        } else {
            tmp += stol(line);
        }
    }
    cout << "Max calories: " << max[0] + max[1] + max[2] << endl;
}
