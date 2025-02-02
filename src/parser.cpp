#include "parser.hpp"

#include <iostream>

Parser::Parser() {
}

void Parser::step() {
    // read the input commands and apply them to the gui
    
}

void Parser::set_gui(Gui *_gui) {
    gui = _gui;
    has_gui = true;
}
