#include <cstddef>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

using Register = int;

struct Cursor {
    int row;
    int col;

    Cursor() : row(0), col(0) {}
    Cursor(int r, int c) : row(r), col(c) {}
};

struct CRT {
    constexpr static size_t width = 40;
    constexpr static size_t height = 6;
    char pixels[height][width];
    int sprite;
    Cursor cursor;

    CRT() : sprite(1), cursor{0, 0} {
        for (size_t h = 0; h < height; ++h) {
            for (size_t w = 0; w < width; ++w) {
                pixels[h][w] = ' ';
            }
        }
    }

    void set_sprite_idx(const int n) {
        sprite = n;
    }

    void move_cursor() {
        if (cursor.col == width - 1) {
            /* Reached end of row */
            ++cursor.row;
            cursor.col = 0;
        } else {
            ++cursor.col;
        }
    }

    void draw() {
        if (cursor.col >= sprite - 1 && 
            cursor.col <= sprite + 1)
        {
            pixels[cursor.row][cursor.col] = '#'; 
        } else {
            pixels[cursor.row][cursor.col] = '.'; 
        }

        move_cursor();
    }
    
    void print() {
        for (size_t h = 0; h < height; ++h) {
            for (size_t w = 0; w < width; ++w) {
                cout << pixels[h][w];
            }
            cout << '\n';
        }
    }
};

int main(void) {
    auto input = utils::read_file("./input");
    Register X = 1;
    CRT crt;

    for (const auto &line : input) {
        auto delim = line.find_first_of(' ');
        string instruction = line.substr(0, delim);

        crt.set_sprite_idx(X);

        if (instruction == "noop") {
            crt.draw();
        } else if (instruction == "addx") {
            int number = 0;

            if (line[delim + 1] == '-') {
                number = stoi(line.substr(delim + 2)) * (-1);
            } else {
                number = stoi(line.substr(delim + 1));
            }

            for (size_t i = 1; i <= 2; ++i) {
                crt.draw();
                if (i == 2) {
                    X += number;
                }
            }
        }
    }
    crt.print();
}
