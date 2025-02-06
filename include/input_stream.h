#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <thread>
#include <atomic>

#include "async_fifo.hpp"

class InputStream {
public:
    static const int INPUT_BUFF_SIZE = 4096;

    InputStream(std::string _path);
    void run();
    void run_async();
    void terminate();
    void assign_command_fifo(sulicat::AsyncFifo<std::string> *fifo_in);

private:
    std::thread run_t;
    bool is_running_thread = false;
    bool has_fifo = false;
    std::atomic<bool> is_running = false;
    sulicat::AsyncFifo<std::string> *fifo = NULL;

    std::string stream_path;
    std::string command_in_path;
    std::fstream command_in;
    std::streampos command_in_pos;
    std::array<char, INPUT_BUFF_SIZE> input_buff;
};