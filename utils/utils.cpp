#include <ios>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <string>
#include <vector>

#include "utils.hpp"

namespace utils {
    [[nodiscard]]
    extern const std::vector<std::string> 
    read_file(const std::filesystem::path& path)
    {
        std::vector<std::string> lines;
        std::ifstream ifs(path, std::ios_base::in);
        assert(ifs.good()); 
        std::string line;    
        while (std::getline(ifs, line)) {
            lines.push_back(line);
        }
        return lines;
    }
}
