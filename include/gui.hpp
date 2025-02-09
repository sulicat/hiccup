#pragma once

#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// singleton class to handle the window and guid events
class Gui {
public:

    struct TabInfo{
        std::string name;
        bool visible;
    };

    static Gui &get();

    void init(std::string title, int w, int h);
    bool is_open();
    void step();
    void terminate();

    void set_tab( std::string _tab_name);
    void label( std::string name, std::string data );
    void num_float( std::string name, float data );

private:
    Gui();
    void _create();
    void resize(int _w, int _h);

    void show_menu_bar();
    void show_main_window();
    void show_debug();

    // gui data
    bool running = true;
    bool show_window = true;
    std::vector<TabInfo> tabs;
    int active_tab = -1;

    // SDL Data
    std::string window_title;
    int window_width;
    int window_height;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_GLContext gl_context;

    static Gui *_instance;
};