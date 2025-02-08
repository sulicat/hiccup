#include <iostream>
#include <algorithm>
#include <functional>

#include "gui.hpp"
#include "ansi.hpp"
#include <GL/gl.h>
#include "gui_style.hpp"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

Gui *Gui::_instance = nullptr;

Gui::Gui() {}

void Gui::_create() {
    std::cout << sulicat::ansi::GREEN << "[GUI]" << sulicat::ansi::RESET
              << " Creating gui\n";
}

Gui &Gui::get() {
    if (_instance == nullptr) {
        _instance = new Gui();
        _instance->_create();
    }
    return *_instance;
}

void Gui::init(std::string title, int w, int h) {
    window_width = w;
    window_height = h;
    window_title = title;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    window = SDL_CreateWindow(window_title.c_str(), window_width, window_height, window_flags);

    renderer = SDL_CreateRenderer(window, NULL);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);
    SDL_ShowWindow(window);

    // imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    setup_gui_style();
    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");
}

bool Gui::is_open() { return running; }

void Gui::resize(int _w, int _h) {
    window_width = _w;
    window_height = _h;
}

void Gui::step() {
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        ImGui_ImplSDL3_ProcessEvent(&event);

        switch (event.type) {
        case SDL_EVENT_QUIT:
            running = false;
            break;

        case SDL_EVENT_WINDOW_RESIZED:
            resize(event.window.data1, event.window.data2);
        }
    }

    glViewport(0, 0, window_width, window_height);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    this->show_menu_bar();
    this->show_main_window();
    this->show_debug();
    // ImGui::ShowDemoWindow();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

void Gui::show_debug() {
    ImGui::Begin("Debug", NULL);

    ImGui::Text("Active Tab: %d\n", active_tab);

    ImGui::End();
}

void Gui::show_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {

            if (ImGui::BeginMenu("Tabs")) {

                for (auto it = tabs.begin(); it != tabs.end(); it++) {
                    ImGui::MenuItem(it->name.c_str(), "", &it->visible);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Gui::show_main_window() {
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    if (ImGui::Begin("Hiccup", &show_window, flags)) {
        // Tabs

        if (ImGui::BeginTabBar("Tabs", ImGuiTabBarFlags_None)) {

            for (auto it = tabs.begin(); it != tabs.end(); it++) {
                if (ImGui::BeginTabItem(it->name.c_str(), &it->visible)) {
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}

void Gui::set_tab(std::string _tab_name) {
    // find the tab with that name

    auto it_tab = std::find_if(tabs.begin(), tabs.end(), [_tab_name](TabInfo &elem) {
        return elem.name == _tab_name;
    });

    TabInfo *tab = NULL;

    // we want to create and update the tab if the tab targeted does not exist
    // if _tab_name is "", then the user did not use a specific tabname
    //  in that case if there are no tabs, then create a default one

    if (_tab_name == "" && tabs.size() <= 0) {
        _tab_name = "default";
    } else if (_tab_name == "") {
        return;
    }

    if (it_tab == tabs.end()) {
        // create new tab
        tabs.push_back(TabInfo{.name = _tab_name,
                               .visible = true});
        tab = &tabs.back();
        active_tab = tabs.size() - 1;
    } else {
        tab = &(*it_tab);
        active_tab = it_tab - tabs.begin();
    }
}

void Gui::terminate() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
