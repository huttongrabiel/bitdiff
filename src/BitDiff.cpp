/*
 * Copyright 2022, Hutton Grabiel
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>

void bit_diff(std::string const& a, std::string const& b, size_t bitstream_size)
{

}

size_t to_size_t(std::string const& str)
{
    size_t result = 0;
    int multiplier = 1;

    for (int i = str.length()-1; i >= 0; i--) {
        result += multiplier * (str[i] - '0');
        multiplier *= 10;
    }

    return result;
}

int main(int argc, char* argv[]) {
    size_t bitstream_size { 0 };

    if (argc < 2) {
        std::cerr << "\033[01;31mError: \033[0mAt the minimum, please provide a file with your two bitstreams for comparison.\nSize flags are preferred as well." << std::endl;
        exit(1);
    }

    if (argv[1][0] == '-' && argv[1][1] == '-' && argc >= 3) {
        std::ifstream input_file(argv[2]);
        if (!input_file.is_open()) {
            std::cerr << "\033[01;31mError: \033[0mFile not found. Check relative file path." << std::endl;
            exit(1);
        }
        std::string string_argv2 = static_cast<std::string>(argv[1]);
        bitstream_size = to_size_t(string_argv2.substr(2, string_argv2.length()-2));
    }
    else if (argc < 3 && argc >=2) {
        std::cerr << "\033[01;33mWarning: \033[0mSize of bitstring not provided. See --help" << std::endl;
        std::ifstream input_file(argv[1]);
        if (!input_file.is_open()) {
            std::cerr << "\033[01;31mError: \033[0mFile not found. Check relative file path and ensure that it is a .txt file." << std::endl;
            exit(1);
        }
    }

    if (!bitstream_size) {
        // Get total count of 0s and 1s in given file/string and divide that by two
        bitstream_size = 5;
        std::cout << bitstream_size << std::endl;
    }
}

