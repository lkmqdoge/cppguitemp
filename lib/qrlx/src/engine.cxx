#include "engine.hpp"
#include "SDL3/SDL_init.h"
#include "imgui_impl_sdl3.h"
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
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                isRunning = 0;
        }
        window->HandleEvents();
        window->Clear();
        app->Render();
        window->SwapBuffers();
    }
}

void Engine::Quit()
{
    window->Clean();
    SDL_Quit();
}

void Engine::RequestClose()
{
    isRunning = 0;
}