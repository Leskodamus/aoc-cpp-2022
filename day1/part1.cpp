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
    long max = 0;
    
    while (getline(ifs, line)) {
        if (line.empty() || ifs.peek() == EOF) {
           max = tmp > max ? tmp : max;
           tmp = 0;
        } else {
            tmp += stol(line);
        }
    }
    cout << "Max calories: " << max << endl;
}
