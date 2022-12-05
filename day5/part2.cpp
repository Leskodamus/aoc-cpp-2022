#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <stack>

#include "../utils/utils.hpp"

using namespace std;

using Crate = string;
using Stacks = vector<stack<Crate>>;

struct Instruction {
    size_t n_moves;
    size_t from;
    size_t to;

    Instruction(const string &inst) {
        std::sscanf(inst.c_str(), "move %lu from %lu to %lu", &n_moves, &from, &to);
        --from; /* idx start from 0, instruction start from 1 */
        --to;   /* idx start from 0, instruction start from 1 */
    }
};

template<typename LineIter>
void init_stacks(const LineIter start, const LineIter end, Stacks &stacks) {
    assert(stacks.size() == 0);

    int idx = 0;
    size_t height = 0, width = start->size();
    for (auto it = start; it != end - 1; ++it) ++height;

    vector<Crate> crates;
    for (int w = 0; w < width; ++w) {
        stack<Crate> stack;
        for (int h = height -1; h >= 0; --h) {
            string line = *(start + h);
            if (line[w] == '[' && line[w + 2] == ']') {
                Crate crate{line[w], line[w+1], line[w+2]};
                stack.push(crate);
            }
        }
        if (!stack.empty())
            stacks.push_back(stack);
    }
}

void move_crate(Instruction &instr, Stacks &stacks) {
    stack<Crate> stack;
    for (auto i = 0; i < instr.n_moves; ++i) {
        auto crate = stacks.at(instr.from).top();
        stack.push(crate);
        stacks.at(instr.from).pop();
    }
    while (!stack.empty()) {
        stacks.at(instr.to).push(stack.top());
        stack.pop();
    }
}

string get_top_crates(const Stacks &stacks) {
    string crates;
    for (auto stack : stacks) {
        crates.append(stack.top());
    }
    return crates;
}

int main(void) {
    auto input = utils::read_file("./input");
    Stacks stacks;
    string msg;
    int sep = 1;

    for (auto line : input) {
        if (!line.empty()) ++sep;
        else break;
    }

    assert(sep <= input.size());
    init_stacks(input.cbegin(), input.cbegin() + sep - 1, stacks);

    for (auto line = input.cbegin() + sep; line != input.cend(); ++line) {
        Instruction instr(*line);
        move_crate(instr, stacks);
    }

    msg = get_top_crates(stacks);

    cout << "Crates on top: " << msg << '\n';
}
