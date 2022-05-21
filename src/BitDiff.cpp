/*
 * Copyright 2022, Hutton Grabiel
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>

// FIXME: There has to be a more elegant way of doing this
void bit_diff(std::string const& bitstream, size_t bitstream_size)
{
    std::string bitstream_a = bitstream.substr(0, bitstream_size);
    std::string bitstream_b = bitstream.substr(bitstream_size, bitstream_size);

    for (size_t i = 0; i < bitstream_size; i++) {
        if (bitstream_a[i] == bitstream_b[i])
            std::cout << "\033[1;32m" << bitstream_a[i] << "\033[0m";
        else
            std::cout << bitstream_a[i];
    }

    std::cout << std::endl;

    std::cout << "--------------------------------" << std::endl;

    for (size_t i = 0; i < bitstream_size; i++) {
        if (bitstream_a[i] == bitstream_b[i])
            std::cout << "\033[1;32m" << bitstream_b[i] << "\033[0m";
        else
            std::cout << bitstream_b[i];
    }
    std::cout << std::endl;

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
    size_t size_flag_size { 0 };
    std::ifstream input_file;

    if (argc < 2) {
        std::cerr << "\033[01;31mError: \033[0mAt the minimum, please provide a file with your two bitstreams for comparison.\nSize flags are preferred as well." << std::endl;
        exit(1);
    }

    // Bad CLI parsing but it works don't hate me
    if (argv[1][0] == '-' && argv[1][1] == '-' && argc >= 3) {
        input_file.open(argv[2]);
        if (!input_file.is_open()) {
            std::cerr << "\033[01;31mError: \033[0mFile not found. Check relative file path." << std::endl;
            exit(1);
        }
        std::string string_argv2 = static_cast<std::string>(argv[1]);
        size_flag_size = to_size_t(string_argv2.substr(2, string_argv2.length()-2));
    }
    else if (argc < 3 && argc >=2) {
        std::cerr << "\033[01;33mWarning: \033[0mSize of bitstring not provided. See --help" << std::endl;
        input_file.open(argv[1]);
        if (!input_file.is_open()) {
            std::cerr << "\033[01;31mError: \033[0mFile not found. Check relative file path and ensure that it is a .txt file." << std::endl;
            exit(1);
        }
    }

    // Get total count of 0s and 1s in given file/string and divide that by two
    char bit = 0;
    std::string bitstream;
    while (input_file.get(bit)) {
        if (bit == '0' || bit == '1') {
            bitstream_size++;
            bitstream.push_back(bit);
        }
    }
    bitstream_size /= 2;

    if (bitstream_size != size_flag_size && size_flag_size != 0) {
        std::cerr << "\033[1;31mError: \033[0mBitstream in file has different size than specified bitstream size." << std::endl;
        exit(1);
    }

    bit_diff(bitstream, bitstream_size);

    input_file.close();
}

