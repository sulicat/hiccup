#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <array>

class InputStream {
public:
    static const int INPUT_BUFF_SIZE = 4096;

    InputStream(std::string _path);
    void run();

private:
    std::string stream_path;
    std::string command_in_path;
    std::fstream command_in;
    std::streampos command_in_pos;
    std::array<char, INPUT_BUFF_SIZE> input_buff;
};