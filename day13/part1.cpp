#include <algorithm>
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <variant>

#include "../utils/utils.hpp"

using namespace std;

struct Value;
using List = vector<Value>;

/* Value can either be an integer or a list (vector) */
struct Value : public variant<int, List> {
    friend auto operator<(const Value &a, const Value &b) -> bool;
};

struct ValueComparator {
    auto operator()(int a, int b) const -> bool {
        return a < b;
    }

    auto operator()(const List &a, const List &b) const -> bool {
        return lexicographical_compare(
            a.cbegin(), a.cend(), 
            b.cbegin(), b.cend()
        );
    }

    auto operator()(int a, const List &b) const -> bool {
        return (*this)(List{Value{a}}, b);
    }

    auto operator()(const List &a, int b) const -> bool {
        return (*this)(a, List{Value{b}});
    }
};

auto operator<(const Value &a, const Value &b) -> bool {
    return visit(ValueComparator{}, a, b);
}

static Value parse(const string &line) {
    Value values{List{}};
    stack<Value*> ptr_stack;
    ptr_stack.push(&values);

    for (size_t i = 0; i < line.size(); ++i) {
        const char c = line[i];
        if (c == '[') {
            /* Opening bracket means creating a new list (vector) */
            /* Note: emplace_back() returns a reference to inserted item */
            ptr_stack.push(
                &get<List>(*ptr_stack.top())
                    .emplace_back(Value{List{}})
            );
        } else if (c == ']') {
            ptr_stack.pop();
        } else if (c == ',') 
            continue;
        else {
            if (line[i+1] == ',' || line[i+1] == ']') {
                /* One digit number, e.g. 0-9 */
                get<List>(*ptr_stack.top()).push_back(
                    Value{stoi(line.substr(i, 1))}
                );
            } else if (line[i+2] == ',' || line[i+2] == ']') {
                /* Two digit number, e.g. 10 */
                get<List>(*ptr_stack.top()).push_back(
                    Value{stoi(line.substr(i, 2))}
                );
                ++i;
            }
        }
    }

    return values;
}

void print_value(const Value &value) {
    if (value.index() == 0)
        cout << get<int>(value) << ' ';
    else {
        for (const auto &v : get<List>(value)) {
            print_value(v);
        }
    }
}

int main(void) {
    auto input = utils::read_file("./input");
    int idx = 0, sum = 0;

    for (auto line = input.cbegin(); line != input.cend(); ++line) {
        if (line->empty()) continue;
        ++idx;
        auto v1 = parse(*line);
        auto v2 = parse(*(line + 1));
        if (v1 < v2) {
            sum += idx;
        }
        ++line;
    }

    cout << "Sum of indices in right order: " << sum << endl;
}
