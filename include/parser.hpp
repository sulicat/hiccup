#pragma once

#include "gui.hpp"

class Parser {
public:
    Parser();
    void step();
    void set_gui(Gui *_gui);

private:
    Gui *gui = NULL;
    bool has_gui = false;
};