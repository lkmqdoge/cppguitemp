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
    app_(std::move(p_app)),
    title_(std::move(p_title))
{
    window_ = Window::Create(title_, this);
    if (!window_->Init(0, 0, p_screenWidth, p_screenHeight))
    {
        LOG("the main window is fucking died in agony");
    }

    app_->MainWindow = window_.get();
    app_->Engine = this;
}

void Engine::Start()
{
    app_->Init();
    app_->Start();
}

void Engine::Run()
{
    for (;isRunning_;)
    {
        isRunning_ = window_->HandleEvents();
        window_->Clear();
        app_->Render();
        window_->SwapBuffers();
    }
}

void Engine::Quit()
{
    app_->Exit();
    window_->Clean();
    SDL_Quit();
}

void Engine::ProccesEvent(SDL_Event* event)
{
    app_->HandleEvent(event);
}

void Engine::RequestClose()
{
    isRunning_ = 0;
}
