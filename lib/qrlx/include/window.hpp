#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL3/SDL_video.h"

namespace qrlx
{
class Window
{
public:
    Window();
    ~Window();

    void Run();
    void RequestClose();

private:

    SDL_Window* window_p;
    void Init();    
    void Update();
    void Quit();
};
}

#endif