#ifndef LIB_AOC_UTILS
#define LIB_AOC_UTILS

#include <string>
#include <vector>
#include <filesystem>

namespace utils {
    [[nodiscard]]
    extern const std::vector<std::string> read_file(const std::filesystem::path&);
} /* namespace utils */

#endif /* LIB_AOC_UTILS */
