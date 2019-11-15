#include "split.h"
#include "sort.h"

#include <string>
#include <iostream>
#include <getopt.h>

void print_usage() {
    std::cout << "Usage:\n"
              << "\t-I, --inputfile\n\t\tFile path to sort.\n"
              << "\t-M, --memlimit\n\t\tMemory limit in MB.\n"
              << "\t-O, --outputfile\n\t\tFile path to output sorted results.\n";
}

static struct option long_options[] =
{
    {"inputfile",       required_argument, 0, 'I'},
    {"memlimit",        required_argument, 0, 'M'},
    {"outputfile",      required_argument, 0, 'O'},
    {"help",            no_argument, 0, '?'},
    {0, 0, 0, 0}
};

int main(int argc, char* const argv[]) {
    int opt = 0;
    int long_index = 0;
    std::string input_file_arg, mem_limit_arg, output_file_arg;

    while ((opt = getopt_long(argc, argv, "I:M:O:?",
            long_options, &long_index )) != -1) {
        switch (opt) {
            case 'I': input_file_arg = optarg; break;
            case 'M': mem_limit_arg = optarg; break;
            case 'O': output_file_arg = optarg; break;
            case '?': print_usage(); return 1;
        }
    }

    // setting mem_limit
    size_t mem_limit;
    sscanf(mem_limit_arg.c_str(), "%zu", &mem_limit);
    mem_limit *= 1024 * 1024;


    // 1st step is to split big file to chunks
    const size_t f_count = split_to_temp_files(input_file_arg, mem_limit);

    // 2nd step sort all temp files
    sort_data(f_count);


    // last we merge sorted files and remove tmp
    merge_sorted_data(f_count, output_file_arg);

    return 0;
}
