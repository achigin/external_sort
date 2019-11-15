#include "split.h"
#include <fstream>
#include <cstdio>

size_t split_to_temp_files(const std::string& file_name, const size_t mem_limit) {
    size_t files_written = 0;
    size_t mem_used = 0;
    std::ifstream input(file_name);
    std::ofstream output(std::to_string(files_written));
    for (std::string line; std::getline(input, line);) {
        if (mem_used + line.size() + 1 > mem_limit) {
            ++files_written;
            output.close();
            output.clear();
            output.open(std::to_string(files_written));
            mem_used = 0;
        }
        output << line << '\n';
        mem_used += line.size() + 1;
    }
    return ++files_written;
}

void clear_temp_files(const size_t file_count) {
    for (size_t i = 0; i < file_count; ++i) {
        std::remove(std::to_string(i).c_str());
    }
}
