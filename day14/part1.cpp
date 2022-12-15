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

using Grid = char[1000][1000];

void init_grid(Grid &grid) {
    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            grid[i][j] = '.';
        }
    }
}

bool is_out_of_bounds(int x, int y) {
    return !((x >= 0 && x < 1000) && (y >= 0 && y < 1000));
}

bool is_out_of_bounds(const Point &point) {
    return is_out_of_bounds(point.x, point.y);
}

int main(void) {
    auto input = utils::read_file("./input");
    Grid grid;
    init_grid(grid);
    Point sand_start_pos{500, 0};
    Point prev_point;
    int sum = 0;
    int max_height = 0;

    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        istringstream iss(*line);
        string coord;

        /* Read the first coordinate which is used as previous point */
        if (!getline(iss, coord, ' ')) break;
        prev_point = {
            stoi(coord.substr(0, coord.find(','))),
            stoi(coord.substr(coord.find(',') + 1))
        };

        while (getline(iss, coord, ' ')) {
            if (coord == "->") continue;

            Point point{
                stoi(coord.substr(0, coord.find(','))),
                stoi(coord.substr(coord.find(',') + 1))
            };

            max_height = max_height < point.y ? point.y : max_height;

            int dx = prev_point.x - point.x;
            int dy = prev_point.y - point.y;

            /* cout << "(" << prev_point.x << "," << prev_point.y << ") -> "; */
            /* cout << "(" << point.x << "," << point.y << ")\n"; */

            for (int i = 0; i <= abs(dx); ++i) {
                if (dx < 0) {
                    grid[point.y][point.x - i] = '#';
                } else {
                    grid[point.y][point.x + i] = '#';
                }
            }

            for (int i = 0; i <= abs(dy); ++i) {
                if (dy < 0) {
                    grid[point.y - i][point.x] = '#';
                } else {
                    grid[point.y + i][point.x] = '#';
                }
            }

            prev_point = point;
        }
    }

    Point sand = sand_start_pos;
    while (true) {
        if (sand.y > max_height) {
            break;
        }

        /* Move down */
        if (!is_out_of_bounds(sand.x, sand.y + 1) && 
                grid[sand.y + 1][sand.x] == '.')
        {
            ++sand.y;
            /* Move diagonally left */
        } else if (!is_out_of_bounds(sand.x - 1, sand.y + 1) && 
                grid[sand.y + 1][sand.x - 1] == '.')
        {
            --sand.x;
            ++sand.y;
            /* Move diagonally right */
        } else if (!is_out_of_bounds(sand.x + 1, sand.y + 1) && 
                grid[sand.y + 1][sand.x + 1] == '.')
        {
            ++sand.x;
            ++sand.y;
        } else {
            ++sum;
            grid[sand.y][sand.x] = 'o';
            sand = sand_start_pos;
        }
    }

    cout << "Number of sand units that can rest: " << sum << endl;
}
