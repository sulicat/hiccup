#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "gui.hpp"
#include "parser.hpp"
#include "sulicat.hpp"

int main(int argc, char **argv) {

    Gui &gui = Gui::get();
    gui.init("Hiccup", 1280, 720);

    Parser parser;
    parser.set_gui( &gui );

    while (gui.is_open()) {

        parser.step();
        gui.step();
    }

    return 0;
}