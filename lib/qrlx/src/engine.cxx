#include "engine.hpp"
#include "SDL3/SDL_init.h"
#include "iapp.hpp"
#include "log.hpp"
#include <utility>

using namespace qrlx;

Engine::Engine(std::unique_ptr<IApp>&& p_app,
               std::string p_title,
               int p_screenWidth,
               int p_screenHeight
            ) :
    app(std::move(p_app)),
    title(std::move(p_title))
{
    window = Window::Create(title);
    if (!window->Init(0, 0, p_screenWidth, p_screenHeight))
    {
        LOG("the main window is fucking died in agony");
    }
}

void Engine::Start()
{
    app->Init();
    app->Start();
}

void Engine::Run()
{
    /*
        - Main loop  
    */
    for (;isRunning;)
    {
        isRunning = window->HandleEvents();
        window->Clear();
        app->Render();
        window->SwapBuffers();
    }
}

void Engine::Quit()
{
    app->Exit();
    window->Clean();
    SDL_Quit();
}

void Engine::RequestClose()
{
    isRunning = 0;
}
