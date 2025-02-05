#include "input_stream.h"
#include "ansi.hpp"
#include <unistd.h>
#include "general_utils.hpp"

InputStream::InputStream(std::string _path) {
    stream_path = _path;
    command_in_path = stream_path + "hiccup_in";

    input_buff = std::array<char, INPUT_BUFF_SIZE>();
}

void InputStream::run() {
    // open for read and write so that it can get created if it doesn't exist
    command_in = std::fstream(command_in_path,
                              std::ios::out | std::ios::in | std::ios::trunc);

    if (!command_in.is_open()) {
        std::cout << sulicat::ansi::RED << "[ERROR] " << sulicat::ansi::RESET << "could not open: " << command_in_path << "\n";

    } else {
        std::cout << sulicat::ansi::GREEN << "[STATUS] " << sulicat::ansi::RESET;
        std::cout << "Opened: " << command_in_path << "\n";
    }

    command_in.seekg(0, std::ios::end);
    command_in_pos = command_in.tellg(); // start it off at the end
    is_running = true;

    while (is_running) {

        command_in.seekg(0, std::ios::end);
        std::streampos current_pos = command_in.tellg();

        if (current_pos > command_in_pos) {

            int diff = current_pos - command_in_pos;
            if (diff < INPUT_BUFF_SIZE) {
                command_in.seekg(command_in_pos);
                command_in.read(input_buff.data(), current_pos - command_in_pos);
            }

            command_in_pos = current_pos;

            sulicat::print_iterable(input_buff, 0, diff);
        }

        usleep(1000); // don't spin lock too hard?
    }
}

void InputStream::run_async() {
    run_t = std::thread(&InputStream::run, this);
    is_running_thread = true;
} 

void InputStream::terminate() {
    is_running = false;
    run_t.join();
}