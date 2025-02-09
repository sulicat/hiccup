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

    // a valid command has more than 1 token (HICCAUP + COMMAND)
    if (tokens.size() <= 1)
        return;

    // TODO: suli single command tokens here

    // 3 token commands
    if (tokens.size() <= 2)
        return;

    TokAttributes command = extract_attributes(tokens[1]);
    if (command["token"] == "LABEL") {
        command_label(command, tokens[2]);
    } else if (command["token"] == "FLOAT") {
        command_float(command, tokens[2]);
    }
}

void Parser::command_label(TokAttributes command, std::string data) {
    gui->label(command["id"], data);
}

void Parser::command_float(TokAttributes command, std::string data) {
    gui->num_float(command["id"], std::atof(data.c_str()));
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
    out["token"] = token_attr[0]; // the token itself

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
