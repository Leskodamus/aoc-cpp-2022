#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <cstring>
#include <tuple>
#include <vector>
#include <queue>

#include "../utils/utils.hpp"

using namespace std;

struct Monkey {
    long long monkey_business_level;
    queue<long long> items;
    tuple<string, char, string> operation;
    long long test;
    long long true_dest, false_dest;

    Monkey() : items{}, operation{"", ' ', ""}, test(1),
               true_dest(-1), false_dest(-1),
               monkey_business_level(0) {}
    
    void calc_worry_level(long long &item) {
        long long old = item;
        long long n;

        if (get<2>(operation) == "old") {
            n = old;
        } else { n = stoul(get<2>(operation)); }
        
        switch (get<1>(operation)) {
            case '+':
                item = old + n;
                break;
            case '-':
                item = old - n;
                break;
            case '*':
                item = old * n;
                break;
            case '/':
                item = old / n;
                break;
        }

        item /= 3;
    }

    long long get_throw_target(long long &item) {
        if (item % test == 0) return true_dest;
        else return false_dest;
    }

    void throw_item(Monkey &monkey) {
        if (items.size() > 0) {
            monkey.items.push(items.front());
            items.pop();
            ++monkey_business_level;
        }
    }

    void print() {
        auto items_cpy(items);
        cout << "Items: ";
        while(!items_cpy.empty()) {
            cout << items_cpy.front() << ' '; 
            items_cpy.pop();
        }
        cout << "\nOperation: " << get<0>(operation) << ' ' << get<1>(operation)
             << ' ' << get<2>(operation) << '\n';
        cout << "Test: divisible by " << test << '\n';
        cout << "If true: " << true_dest << "\nIf false: " << false_dest << '\n';
    }
};

void parse_input(const vector<string> &input, vector<Monkey> &monkeys) {
    Monkey monkey;
    string starting_items = "  Starting items: ";
    string operation = "  Operation: ";
    string test = "  Test: ";
    string if_true = "    If true: ";
    string if_false = "    If false: ";

    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        if (line->find(starting_items) != string::npos) {
            string numbers = line->substr(starting_items.size()); 
            auto n = strtok(strdup(numbers.c_str()), ", ");
            while (n) {
                monkey.items.push(strtoull(n, nullptr, 10));
                n = strtok(nullptr, ", ");
            }
        } else if (line->find(operation) != string::npos) {
            string str;
            istringstream iss(*line);
            iss >> str >> str >> str;
            iss >> get<0>(monkey.operation);
            iss >> get<1>(monkey.operation);
            iss >> get<2>(monkey.operation);
        } else if (line->find(test) != string::npos) {
            string str; 
            istringstream iss(*line);
            iss >> str >> str >> str;
            iss >> monkey.test;
        } else if (line->find(if_true) != string::npos) {
            string str; 
            istringstream iss(*line);
            iss >> str >> str >> str >> str >> str;
            iss >> monkey.true_dest;
        } else if (line->find(if_false) != string::npos) {
            string str; 
            istringstream iss(*line);
            iss >> str >> str >> str >> str >> str;
            iss >> monkey.false_dest;
        }

        if (line->empty() || line + 1 == input.cend()) {
            monkeys.push_back(monkey);
            monkey = Monkey();
        }
    }
}

int main(void) {
    auto input = utils::read_file("./input");
    vector<Monkey> monkeys;
    long long mb = 0;

    parse_input(input, monkeys);

    /* Number of rounds (20) */
    for (size_t i = 0; i < 20; ++i) {
        /* For each monkey */
        for (auto &monkey : monkeys) {
            /* Throw all its items */
            while (!monkey.items.empty()) {
                auto &item = monkey.items.front();
                monkey.calc_worry_level(item);
                auto dest = monkey.get_throw_target(item);
                monkey.throw_item(monkeys.at(dest)); 
            }
        }
    }

    vector<long long> mb_levels;
    for (const auto &monkey : monkeys) {
        mb_levels.push_back(monkey.monkey_business_level);
    }
    sort(mb_levels.rbegin(), mb_levels.rend());
    mb = mb_levels.at(0) * mb_levels.at(1);

    cout << "Level of monkey business: " << mb << endl;
}
