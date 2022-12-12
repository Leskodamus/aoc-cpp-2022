#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

#include "../utils/utils.hpp"

using namespace std;

template <typename T>
using Grid = vector<vector<T>>;

static constexpr int movement[2][4] = {
    {-1, 1, 0, 0},  /* x */
    {0, 0, 1, -1}   /* y */
};

int main(void) {
    auto input = utils::read_file("./input");
    Grid<int> grid, dist;
    Grid<bool> visited;
    pair<int, int> start, end;
    int steps = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        const auto &line = input[i];
        vector<int> row;

        for (size_t j = 0; j < line.length(); ++j) {
            if (line[j] == 'S') {
                start = make_pair(i, j);
                row.push_back(0);   /* min */
            } else if (line[j] == 'E') {
                end = make_pair(i, j);
                row.push_back('z' - 'a');   /* max */
            } else {
                row.push_back(line[j] - 'a');   /* Between min and max */
            }
        }

        grid.push_back(row);
        visited.push_back(vector<bool>(row.size(), false));
        dist.push_back(vector<int>(row.size(), 0));
    }

    queue<pair<int, int>> que;
    que.push(start);
    while (!que.empty()) {
        pair<int, int> curr = que.front();
        que.pop();

        for (size_t i = 0; i < 4; ++i) {
            int next_x = curr.first + movement[0][i];
            int next_y = curr.second + movement[1][i];

            /* Check for out of bounds */
            if (next_x < 0 || next_x >= grid.size() || 
                next_y < 0 || next_y >= grid[0].size()) 
            { continue; }

            /* Check if already visited */
            if (visited[next_x][next_y]) continue;

            /* Check if we can move */
            if (grid[next_x][next_y] - grid[curr.first][curr.second] <= 1) {
                dist[next_x][next_y] = dist[curr.first][curr.second] + 1;
                visited[next_x][next_y] = true;
                que.push(make_pair(next_x, next_y));
            }
        }
    }

    steps = dist[end.first][end.second];

    cout << "Shortest path to destination: " << steps << endl;
}
