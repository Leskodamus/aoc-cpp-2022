#include <climits>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

struct Point {
    int x = 0;
    int y = 0;
};

class Sensor {
    public:
        Point pos;
        Point beacon;

        [[nodiscard]] constexpr int manhatten() {
            return abs(pos.x - beacon.x) + abs(pos.y - beacon.y);
        }

        void print() {
            cout << '(' << pos.x << ',' << pos.y << ')' << "->" << '(' << beacon.x << ',' << beacon.y << ')' << endl;
        }
};

int main(void) {
    auto input = utils::read_file("./input");
    vector<Sensor> sensors;
    vector<int> dists;
    vector<pair<int, int>> intervals;
    long sum = 0;

    /* Read in all sensors with their beacon */
    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        Sensor sensor;
        sscanf(line->c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
               &sensor.pos.x, &sensor.pos.y, &sensor.beacon.x, &sensor.beacon.y);
        sensors.push_back(sensor);
        dists.push_back(sensor.manhatten());
    }

    vector<int> pos_lines;
    vector<int> neg_lines;
    for (int i = 0; i < sensors.size(); ++i) {
        const auto &s = sensors.at(i);
        auto d = dists[i];
        pos_lines.push_back(s.pos.x - s.pos.y - d);
        pos_lines.push_back(s.pos.x - s.pos.y + d);
        neg_lines.push_back(s.pos.x + s.pos.y - d);
        neg_lines.push_back(s.pos.x + s.pos.y + d);
    }

    int pos = 0, neg = 0;
    for (int i = 0; i < 2 * sensors.size(); ++i) {
        for (int j = i + 1; j < 2 * sensors.size(); ++j) {
            int a = pos_lines[i], b = pos_lines[j];
            if (abs(a - b) == 2)
                pos = min(a, b) + 1;

            a = neg_lines[i];
            b = neg_lines[j];

            if (abs(a - b) == 2)
                neg = min(a, b) + 1;
        }
    }

    long x = (pos + neg) / 2; 
    long y = (neg - pos) / 2;
    sum = x * 4000000 + y;

    cout << "Number of positions that cannot be a beacon: " << sum << endl;
}
