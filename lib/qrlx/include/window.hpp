#ifndef QRLX_WINDOW_HPP
#define QRLX_WINDOW_HPP

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

class Window
{
public:
    Window(std::string p_title);
    ~Window();
    
    // Init 
    bool Init(int p_xPos, int p_yPos, int p_width, int p_height);
    void Clean();

    static std::unique_ptr<Window> Create(const std::string& p_title);
    

    bool HandleEvents();

    // Draw
    void Clear();
    void SwapBuffers();

    // Properties
    Color& GetDefaultClearColor();
    void SetDefaultClearColor(Color p_color);
    
private:
    Color defaultClearColor { Color(0.6f, 0.5f, 0.7f, 1.0f) };
    std::unique_ptr<SDL_Window, SdlWindowDestroyer> window;
    SDL_GLContext context {};
    std::string title;
    ImGuiIO* io;
};
}

#endif
