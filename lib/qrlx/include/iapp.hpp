#ifndef QRLX_IAPP_HPP_
#define QRLX_IAPP_HPP_

#include "SDL3/SDL_events.h"
#include "window.hpp"

namespace qrlx
{

class Engine;

class IApp
{
public:
    virtual void Init()                         = 0;
    virtual void Start()                        = 0;
    virtual void Update()                       = 0;
    virtual void Render()                       = 0;
    virtual void Exit()                         = 0;
    virtual void HandleEvent(SDL_Event* event)  = 0;

    Window* MainWindow;
    Engine* Engine;
};
}

#endif
