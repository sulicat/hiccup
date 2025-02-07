#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "gui.hpp"
#include "parser.hpp"
#include "ansi.hpp"
#include "file_utils.hpp"
#include "input_stream.h"
#include "input_repl.h"
#include "async_fifo.hpp"

int main(int argc, char **argv) {

    sulicat::AsyncFifo<std::string> command_fifo;

    InputStream input_stream(sulicat::file::folder_path("/var/tmp/"));
    input_stream.assign_command_fifo(&command_fifo);
    input_stream.run_async();

    InputRepl input_repl;
    input_repl.run_async();

    Gui &gui = Gui::get();
    gui.init("Hiccup", 1280, 720);

    Parser parser;
    parser.set_gui(&gui);

    while (gui.is_open()) {
        while(command_fifo.size() > 0){
            std::string command = command_fifo.pop();
            std::cout << "COMMAND: " << command << "\n";
        }

        parser.step();
        gui.step();
    }

    gui.terminate();
    input_stream.terminate();
    input_repl.terminate();

    return 0;
}