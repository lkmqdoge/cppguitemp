#ifndef QRLX_WINDOW_HPP_
#define QRLX_WINDOW_HPP_

#include "SDL3/SDL_video.h"
#include "color.hpp"
#include "imgui.h"
#include <memory>
#include <string>

namespace qrlx
{

struct SdlWindowDestroyer {
    void operator()(SDL_Window* window) const {
        SDL_DestroyWindow(window);
    }
};

class Engine; // fd for engine.hpp

class Window
{

public:
    Window(std::string p_title, Engine* en);
    ~Window();

    static std::unique_ptr<Window> Create(const std::string& p_title, Engine* engine);

    // Init
    bool Init(int p_xPos, int p_yPos, int p_width, int p_height);
    void Clean();
    bool HandleEvents();
    void Clear();
    void SwapBuffers();

    Color& GetDefaultClearColor();
    void SetDefaultClearColor(Color p_color);

    int GetWidth();
    int GetHeight();

    float GetFramerate();

private:

    int width_;
    int height_;
    std::string title_;
    Engine* engine_;
    ImGuiIO* io_;
    Color default_clear_color_ { Color(0.6f, 0.5f, 0.7f, 1.0f) };
    std::unique_ptr<SDL_Window, SdlWindowDestroyer> window_;
    SDL_GLContext context_ {};

    void UpdateWindowSize();
};
}

#endif
