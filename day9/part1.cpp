#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

#include "../utils/utils.hpp"

using namespace std;

enum class Direction {
    LEFT = 'L',
    RIGHT = 'R',
    UP = 'U',
    DOWN = 'D',
    UNKNOWN = '\0'
};

ostream &operator<<(ostream &os, const Direction &dir) {
    os << static_cast<char>(dir);
    return os;
}

struct Position {
    int x;
    int y;

    Position() : x(0), y(0) {}

    void move_position(const Direction &dir, const size_t steps) {
        if (dir == Direction::LEFT)
            x -= steps;
        if (dir == Direction::RIGHT)
            x += steps;
        if (dir == Direction::UP)
            y += steps;
        if (dir == Direction::DOWN)
            y -= steps;
    }

    inline bool operator==(const Position &pos) const {
        return x == pos.x && y == pos.y; 
    }

    struct PositionHash {
        int64_t operator() (const Position &pos) const {
            int32_t xHash = static_cast<int32_t>(pos.x);
            int32_t yHash = static_cast<int32_t>(pos.y);
            return (static_cast<int64_t>(xHash) << 32) | yHash;
        }
    };
};

struct Rope {
    Position head;
    Position tail;
    /* vector<Position> pos_visited_by_tail; */
    unordered_set<Position, Position::PositionHash> pos_visited_by_tail;

    void move_head(const Direction &dir, size_t steps) {
        /* Move one by one */
        while (steps > 0) {
            head.move_position(dir, 1);

            if (head.x == tail.x || head.y == tail.y) {
                /* Head and tail in same row or col means no diagonal move */
                /* Move the tail towards the head */
                if (head.x - 1 > tail.x)
                    tail.move_position(Direction::RIGHT, 1);
                else if (head.x < tail.x - 1)
                    tail.move_position(Direction::LEFT, 1);
                else if (head.y - 1 > tail.y)
                    tail.move_position(Direction::UP, 1);
                else if (head.y < tail.y - 1)
                    tail.move_position(Direction::DOWN, 1);
            } else {
                /* Top left */
                if ((head.x == tail.x - 1 && head.y == tail.y + 2) ||
                    (head.x == tail.x - 2 && head.y == tail.y + 1)) 
                {
                    tail.move_position(Direction::LEFT, 1);
                    tail.move_position(Direction::UP, 1);
                }
                /* Top right */
                else if ((head.x == tail.x + 1 && head.y == tail.y + 2) ||
                         (head.x == tail.x + 2 && head.y == tail.y + 1))
                {
                    tail.move_position(Direction::RIGHT, 1);
                    tail.move_position(Direction::UP, 1);
                }
                /* Bottom left */
                else if ((head.x == tail.x - 2 && head.y == tail.y - 1) ||
                         (head.x == tail.x - 1 && head.y == tail.y - 2))
                {
                    tail.move_position(Direction::LEFT, 1);
                    tail.move_position(Direction::DOWN, 1);
                }
                /* Bottom right */
                else if ((head.x == tail.x + 2 && head.y == tail.y - 1) ||
                         (head.x == tail.x + 1 && head.y == tail.y - 2))
                {
                    tail.move_position(Direction::RIGHT, 1);
                    tail.move_position(Direction::DOWN, 1);
                }
            }

            /* Save visited position */
            if (find(pos_visited_by_tail.cbegin(), pos_visited_by_tail.cend(), tail) 
                == pos_visited_by_tail.cend())
            {
                /* pos_visited_by_tail.push_back(tail); */
                pos_visited_by_tail.insert(tail);
            }

            --steps;
        }
    }
};

Direction parse_direction(const char d) {
    if (d == 'L')
        return Direction::LEFT;
    if (d == 'R')
        return Direction::RIGHT;
    if (d == 'U')
        return Direction::UP;
    if (d == 'D')
        return Direction::DOWN;
    else
        return Direction::UNKNOWN;
}

int main(void) {
    auto input = utils::read_file("./input");
    Rope rope;
    int res = 0;

    for (const auto &line : input) {
        auto direction = parse_direction(line[0]);
        size_t steps = stoul(string{line.begin() + 2, line.end()});
        rope.move_head(direction, steps); 
    }

    res = rope.pos_visited_by_tail.size();

    cout << "Number of visited positions of the tail: " << res << endl;
}
