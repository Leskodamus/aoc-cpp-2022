#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

using namespace std;

static const size_t AVAILABLE_DISK_SPACE = 70000000;
static const size_t NEEDED_FREE_SPACE = 30000000;

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

    size_t get_dir_size() const {
        size_t size = 0;

        for (const auto &file : this->files) {
            size += file.size;
        } 

        for (const auto &subdir : this->subdirs) {
            size += subdir.get_dir_size();
        }

        return size;
    }
};

bool is_number(const string &str) {
    for (auto &c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

void get_all_dirs(const Directory &dir, vector<Directory> &dirs) {
    dirs.push_back(dir);
    for (auto &subdir : dir.subdirs)
        get_all_dirs(subdir, dirs);
}

int main(void) {
    auto input = utils::read_file("./input");
    Directory root{"/", nullptr, {}, {}};
    root.parent = &root;
    Directory *cwd = &root;

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

    const size_t used_space = root.get_dir_size();
    const size_t unused_space = AVAILABLE_DISK_SPACE - used_space;
    const size_t size_to_free = NEEDED_FREE_SPACE - unused_space;
    size_t size = used_space;
    string dir_name;

    vector<Directory> dirs;
    get_all_dirs(root, dirs);

    for (const auto &dir : dirs) {
        size_t dir_size = dir.get_dir_size();
        if (dir_size < size && dir_size >= size_to_free) {
            dir_name = dir.name;
            size = dir_size;
        }
    }

    cout << "Delete dir: " << dir_name << " with size: " << size << endl;
}
