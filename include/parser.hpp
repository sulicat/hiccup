#pragma once

#include "gui.hpp"
#include <vector>
#include <string>

class Parser {
public:
    Parser();
    void step();
    void set_gui(Gui *_gui);
    void new_command(std::string _new_command);
    std::vector<std::string> get_tokens(const std::string &_in_command);
    void parse_tokens( std::vector<std::string>& tokens );

    void command_tab( std::string tab_name );

private:
    Gui *gui = NULL;
    bool has_gui = false;
};