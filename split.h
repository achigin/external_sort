#pragma once

#include <string>

size_t split_to_temp_files(const std::string& file_name, const size_t mem_limit);
void clear_temp_files(const size_t file_count);
