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

static constexpr int Y = 2000000;

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
    int sum = 0;

    /* Read in all sensors with their beacon */
    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        Sensor sensor;
        sscanf(line->c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
               &sensor.pos.x, &sensor.pos.y, &sensor.beacon.x, &sensor.beacon.y);
        sensors.push_back(sensor);
        dists.push_back(sensor.manhatten());
    }

    /* Calculate intervals (x) */
    for (int i = 0; i < sensors.size(); ++i) {
        const auto &s = sensors.at(i);
        auto dx = dists[i] - abs(s.pos.y - Y);
        if (dx <= 0)
            continue;
        intervals.emplace_back(s.pos.x - dx, s.pos.x + dx);
    }

    /* Get all x pos which are allowed */
    vector<int> allowed;
    for (const auto &s : sensors) {
        if (s.beacon.y == Y)
            allowed.push_back(s.beacon.x);
    }

    /* Get min and max of intervals */
    int x_min = INT_MAX;
    int x_max = INT_MIN;
    for (const auto &p : intervals) {
        const auto &left = get<0>(p);
        const auto &right = get<1>(p);
        x_min = left < x_min ? left : x_min;
        x_max = right > x_max ? right : x_max;
    }

    /* Check if allowed or not */
    for (int i = x_min; i <= x_max; ++i) {
        if (find(allowed.cbegin(), allowed.cend(), i) != allowed.cend())
            continue;

        for (auto &iv : intervals) {
            if (get<0>(iv) <= i && i <= get<1>(iv)) {
                ++sum;
                break;
            }
        }
    }

    cout << "Number of positions that cannot be a beacon: " << sum << endl;
}
