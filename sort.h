#pragma once
#include <string>

void sort_data(const size_t file_count);
void sort_file(const std::string& file_name);

void merge_two_sorted_files(const std::string& file_one, const std::string& file_two, const std::string& out_file);
void merge_sorted_data(const size_t file_count, const std::string& file_name);
