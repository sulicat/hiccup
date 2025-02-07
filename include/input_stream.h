#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <thread>
#include <atomic>
#include <cstring>

#include "async_fifo.hpp"

class InputStream {
public:
    static const int INPUT_BUFF_SIZE = 4096;
    static const int MAX_LINE_LENGTH = 1024;

    static const char CHAR_LINE_END = '\n';

    InputStream(std::string _path);
    void run();
    void run_async();
    void terminate();
    void assign_command_fifo(sulicat::AsyncFifo<std::string> *fifo_in);
    void new_data(char *data, int data_size);
    void complete_line();

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
    std::array<char, INPUT_BUFF_SIZE> input_buff; // buffer to capture new data arriving in file
    std::array<char, MAX_LINE_LENGTH> line_buff;  // buffer to capture the current line, end on a new line
    int line_buff_i = 0;
};