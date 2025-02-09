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

    TokAttributes hiccaup_attr = extract_attributes(tokens[0]);
    command_tab(hiccaup_attr["id"]); // create or set the tab to the commanded tab
}

void Parser::command_tab(std::string tab_name) {
    if (gui == NULL || !has_gui)
        return;

    gui->set_tab(tab_name);
}

std::vector<std::string> Parser::get_tokens(const std::string &_in_command) {
    return sulicat::string_split(_in_command, " ");
}

Parser::TokAttributes Parser::extract_attributes(std::string token) {
    // TOKEN could looks something like this:
    //  TOK
    //  TOK#myid,color=red,age=5 // with ID

    TokAttributes out;
    out["id"] = DEFAULT_TAB;

    std::vector<std::string> token_attr = sulicat::string_split(token, "#");
    if (token_attr.size() == 2) {
        // TODO: suli add the style attributes and what not
        // for now assume the ID is all that follows
        out["id"] = token_attr[1];
    }

    return out;
}

void Parser::set_gui(Gui *_gui) {
    gui = _gui;
    has_gui = true;
}
