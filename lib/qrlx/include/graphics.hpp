#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "SDL3/SDL_video.h"
#include "color.hpp"

namespace qrlx 
{
class Graphics
{
public:
    ~Graphics();
    Graphics();

    void Init();
    void Draw();

    SDL_GLContext& GetContext();
    
    Color& GetDefaultClearColor();
    void SetDefaultClearColor(Color& color);

private:
    Color defaultClearColor;
    
    SDL_Window *window;
    SDL_GLContext *context;
};
}

#endif