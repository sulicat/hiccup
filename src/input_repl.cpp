#include "input_repl.h"
#include "ansi.hpp"
#include <iostream>

InputRepl::InputRepl() {}

void InputRepl::run() {

    terminal.init();
    terminal.set_canonical_mode(false);
    terminal.set_echo(false);

    std::cout << sulicat::ansi::GREEN << "[REPL] " << sulicat::ansi::RESET;
    std::cout << " Starting REPL\n";
    is_running = true;

    while (is_running) {
        char c;
        std::cin.get(c);
        std::cout << " o: " << c << "\n";
    }

    terminal.revert();

}

void InputRepl::run_async() {
    is_async = true;
    run_t = std::thread(&InputRepl::run, this);
}

void InputRepl::terminate() {
    is_running = false;

    if (is_async) {
        run_t.join();
    }
}
