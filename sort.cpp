#include "sort.h"

#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

void sort_file(const std::string& file_name) {
    std::ifstream input(file_name);
    std::vector<std::string> file_content;
    for (std::string line; std::getline(input, line);) {
        file_content.push_back(line);
    }
    input.close();
    input.clear();
    std::sort(file_content.begin(), file_content.end());
    std::ofstream output(file_name);
    for (const auto& line : file_content) {
        output << line << '\n';
    }
}

void sort_data(const size_t file_count) {
    for (size_t i = 0; i < file_count; ++i) {
        sort_file(std::to_string(i));
    }
}

void merge_two_sorted_files(const std::string& file_one, const std::string& file_two, const std::string& out_file) {
    std::ifstream in1(file_one);
    std::ifstream in2(file_two);
    std::ofstream out(out_file);
    std::string line;
    std::string in1s, in2s;


    if (in1) {
        std::getline(in1, in1s);
    }
    if (in2) {
        std::getline(in2, in2s);
    }

    bool ff = true;
    while (in1 || in2) {
        if (in1 && in2) {
            if (in1s.compare(in2s) >= 0) {
                out << in2s << '\n';
                std::getline(in2, in2s);
            } else {
                out << in1s << '\n';
                std::getline(in1, in1s);
            }
        } else {
            if (ff) {
                if (!in1) {
                    out << in2s << '\n';
                } else {
                    out << in1s << '\n';
                }
            } else {
                out << line << '\n';
            }

            if (in1) {
                std::getline(in1, line);
            } else {
                std::getline(in2, line);
            }
            ff = false;
        }
    }
}

void merge_sorted_data(const size_t file_count, const std::string& file_name) {
    std::vector<size_t> files;
    for (size_t i = 0; i < file_count; ++i) {
        files.push_back(i);
    }
    while (files.size() > 0) {
        std::vector<std::pair<size_t, size_t>> merge_pairs;
        const size_t psize = files.size();
        size_t left_alone;
        bool is_left_alone = false;
        for (size_t i = 0; i < psize; i += 2) {
            if (i + 1 < psize) {
                merge_pairs.push_back(std::make_pair(files[i], files[i + 1]));
            } else {
                left_alone = files[i];
                is_left_alone = true;
            }
        }
        files.clear();
        for (const auto& p : merge_pairs) {
            size_t f1 = p.first;
            size_t f2 = p.second;
            size_t fmin = std::min(f1, f2);
            std::string min_out = std::to_string(fmin);
            std::string new_out = std::string("-") + min_out;
            merge_two_sorted_files(std::to_string(f1), std::to_string(f2), new_out);
            std::remove(std::to_string(f1).c_str());
            std::remove(std::to_string(f2).c_str());
            std::rename(new_out.c_str(), min_out.c_str());
            files.push_back(fmin);
        }
        if (!files.size()) {
            std::rename(std::to_string(left_alone).c_str(), file_name.c_str());
        } else if (is_left_alone) {
            files.push_back(left_alone);
        }
    }
}
