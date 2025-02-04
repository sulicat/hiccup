#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <thread>
#include <atomic>

class InputStream {
public:
    static const int INPUT_BUFF_SIZE = 4096;

    InputStream(std::string _path);
    void run();
    void run_async();
    void term();

private:
    std::thread run_t;
    bool is_running_thread = false;
    std::atomic<bool> is_running = false;

    std::string stream_path;
    std::string command_in_path;
    std::fstream command_in;
    std::streampos command_in_pos;
    std::array<char, INPUT_BUFF_SIZE> input_buff;
};