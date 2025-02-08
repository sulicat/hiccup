#include "parser.hpp"
#include "ansi.hpp"
#include "general_utils.hpp"

#include <iostream>

Parser::Parser() {
}

void Parser::step() {
    // read the input commands and apply them to the gui
}

void Parser::new_command(std::string _new_command) {
    std::cout << sulicat::ansi::YELLOW << "-> " << sulicat::ansi::RESET;
    std::cout << " " << _new_command << "\n";

    // split by spaces
    std::vector<std::string> tokens = get_tokens(_new_command);
    sulicat::print_iterable(tokens, "|");
    parse_tokens(tokens);
}

void Parser::parse_tokens(std::vector<std::string> &tokens) {
    if (tokens.size() < 1) {
        // we just got a newline;
        return;
    }

    auto first_arg = sulicat::string_split(tokens[0], "#");
    if (first_arg[0] != "HICCUP") {
        return; // case where this wasn't a command.
    }

    if (tokens.size() == 1) {
        if (first_arg.size() == 2) {
            command_tab(first_arg[1]);
        }
    }
}

void command_tab(std::string tab_name) {
    if (gui == NULL || !has_gui)
        return;

    gui->set_tab(tab_name);
}

std::vector<std::string> Parser::get_tokens(const std::string &_in_command) {
    return sulicat::string_split(_in_command, " ");
}

void Parser::set_gui(Gui *_gui) {
    gui = _gui;
    has_gui = true;
}
