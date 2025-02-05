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

int main(int argc, char **argv) {

    InputStream input_stream(sulicat::file::folder_path("/var/tmp/"));
    input_stream.run_async();

    InputRepl input_repl;
    input_repl.run_async();

    Gui &gui = Gui::get();
    gui.init("Hiccup", 1280, 720);

    Parser parser;
    parser.set_gui(&gui);

    while (gui.is_open()) {
        parser.step();
        gui.step();
    }

    gui.terminate();
    input_stream.terminate();
    input_repl.terminate();

    return 0;
}