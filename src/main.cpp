#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "gui.hpp"
#include "parser.hpp"
#include "sulicat.hpp"

int main(int argc, char **argv) {

    Parser parser;

    Gui &gui = Gui::get();
    gui.init("Hiccup", 1280, 720);

    parser.set_gui( &gui );

    while (gui.is_open()) {

        parser.step();
        gui.step();
    }

    return 0;
}