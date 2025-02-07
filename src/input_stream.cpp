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
            new_data(&input_buff[0], diff);

            // sulicat::print_iterable(input_buff, 0, diff);
            // // TODO: look for new line here, work in cannonical mode
            // if ( has_fifo && fifo != NULL ){
            //     fifo->push("SOMETHING");
            // }
        }

        usleep(1000); // don't spin lock too hard?
    }
}

void InputStream::new_data(char *data, int data_size) {

    for (int i = 0; i < data_size; i++) {

        if (data[i] == CHAR_LINE_END) {
            // check to see if the data we are about to add is within
            // the total line size
            if (i + line_buff_i < MAX_LINE_LENGTH) {

                // copy and complete the line
                memcpy(&line_buff[line_buff_i], data, i);
                line_buff_i += i;
                complete_line();

                if (i < data_size - 1) {
                    // start the next line
                    memcpy(&line_buff[0], data + i+1, data_size - i);
                    line_buff_i = data_size - i-1;
                }

                return;
            }
        }
    }

    // we didn't find a new line, move the whole contents into line if there is space
    if (data_size + line_buff_i < MAX_LINE_LENGTH) {
        memcpy(&line_buff[line_buff_i], data, data_size);
        line_buff_i += data_size;
    }
}

void InputStream::complete_line() {
    std::string s(line_buff.begin(), line_buff.begin() + line_buff_i);
    std::cout << "NEW STRING: " << s << "\n";
    line_buff_i = 0;
}

void InputStream::assign_command_fifo(sulicat::AsyncFifo<std::string> *fifo_in) {
    if (fifo_in != NULL) {
        fifo = fifo_in;
        has_fifo = true;
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