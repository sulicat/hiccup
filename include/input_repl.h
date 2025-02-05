#pragma once

#include "term.hpp"
#include <atomic>
#include <thread>

class InputRepl {
public:
    InputRepl();
    void run();
    void run_async();
    void terminate();

private:
    std::atomic<bool> is_running = false;
    bool is_async = false;
    std::thread run_t;
    sulicat::Term terminal;
};