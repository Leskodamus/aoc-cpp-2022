#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

using Token = string;

struct File {
    string name;
    size_t size;
};

struct Directory {
    string name;
    Directory *parent;
    vector<Directory> subdirs;
    vector<File> files;

    void add_subdir(Directory dir) {
        subdirs.push_back(dir);
    }

    void add_file(File file) {
        files.push_back(file);
    }
};

bool is_number(const string &str) {
    for (auto &c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

size_t add_file_sizes(const Directory &dir, size_t &total_size) {
    size_t cwd_size = 0;

    for (const auto &file : dir.files) {
        cwd_size += file.size;
    }

    for (const auto &subdir : dir.subdirs) {
        cwd_size += add_file_sizes(subdir, total_size);
    }

    if (cwd_size < 100000)
        total_size += cwd_size;

    return cwd_size;
}

int main(void) {
    auto input = utils::read_file("./input");
    Directory root{"/", nullptr, {}, {}};
    root.parent = &root;
    Directory *cwd = &root;
    size_t sum = 0;

    for (auto &line : input) {
        istringstream iss(line);
        Token token;
        vector<decltype(token)> tokens;
        while (getline(iss, token, ' '))
            tokens.push_back(token);

        /*
         * Command (only care about 'cd'):
         * 0 ... $
         * 1 ... cd
         * 2 ... <TARGET>
         *
         * Output:
         * 0 ... <dir>|<SIZE>
         * 1 ... <FILENAME>|<DIRNAME>
         */
        if (tokens.at(0) == "$") {
            if (tokens.at(1) == "cd") {
                if (tokens.at(2) == "/" || tokens.at(2).empty()) {
                    cwd = &root;
                } else if (tokens.at(2) == "..") {
                    cwd = cwd->parent;
                } else {
                    for (auto &subdir : cwd->subdirs) {
                        if (tokens.at(2) == subdir.name) {
                            cwd = &subdir;
                            break;
                        }
                    }
                }
            }
        } 
        else if (tokens.at(0) == "dir") {
            Directory dir{tokens.at(1), cwd, {}, {}};
            cwd->add_subdir(dir);
        }
        else if (is_number(tokens.at(0))) {
            size_t fsize = std::strtoul(tokens.at(0).c_str(), nullptr, 10);
            File file{tokens.at(1), fsize};
            cwd->add_file(file);
        }
    }

    add_file_sizes(root, sum);

    cout << "Sum of total sizes of directories: " << sum << endl;
}
