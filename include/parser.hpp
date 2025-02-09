#pragma once

#include "gui.hpp"
#include <vector>
#include <string>
#include <map>

class Parser {
public:

    static constexpr char* DEFAULT_TAB = (char*)"#";

    // map with attributed attached to a given token
    typedef std::map<std::string, std::string> TokAttributes;

    Parser();
    void step();
    void set_gui(Gui *_gui);
    void new_command(std::string _new_command);
    std::vector<std::string> get_tokens(const std::string &_in_command);

    void parse_tokens( std::vector<std::string>& tokens );
    TokAttributes extract_attributes( std::string token );

    void command_tab( std::string tab_name );

private:
    Gui *gui = NULL;
    bool has_gui = false;
};