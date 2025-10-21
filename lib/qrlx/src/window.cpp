#include "SDL3/SDL_log.h"
#include "engine.hpp"
#include "glad/glad.h"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_events.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "imgui.h"

#include "window.hpp"
#include "log.hpp"
#include <memory>

using namespace qrlx;

Window::Window(std::string p_title, Engine* engine)
    : title_(std::move(p_title)), engine_(engine)
{

}

Window::~Window()
{

}

std::unique_ptr<Window> Window::Create(const std::string &p_title, Engine* engine)
{
    return std::make_unique<Window>(p_title, engine);
}

bool Window::Init(int p_xPos, int p_yPos, int p_width, int p_height)
{

    SDL_WindowFlags flags = SDL_WINDOW_OPENGL
                          | SDL_WINDOW_HIDDEN
                          | SDL_WINDOW_RESIZABLE
                          | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        LOG("Can't Initialize SDL!") << SDL_GetError();
        return false;
    }

    LOG("SDL Initialized!");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window_ = std::unique_ptr<SDL_Window, SdlWindowDestroyer>(
        SDL_CreateWindow(title_.c_str(), p_width, p_height, flags));
    if (!window_)
    {
        LOG("Can't Initialize Widnow!") << SDL_GetError();
        return false;
    }

    width_  = p_width;
    height_ = p_height;

    context_ = SDL_GL_CreateContext(window_.get());
    if (!context_)
    {
        LOG("Can't Create GL Context!") << SDL_GetError();
        return false;
    }

    SDL_GL_MakeCurrent(window_.get(), context_);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        LOG("Failed to initialize GLAD");
        return false;
    }

    SDL_SetWindowPosition(window_.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window_.get());

    SDL_GL_SetSwapInterval(0); // Enable vsync

    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io_ = &ImGui::GetIO();

    // Disable ini files
    io_->IniFilename = NULL;
    io_->LogFilename = NULL;
    io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    ImGui::StyleColorsClassic();
    ImGuiStyle& style = ImGui::GetStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(window_.get(), context_);
    ImGui_ImplOpenGL3_Init();

    return true;
}

void Window::Clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DestroyContext(context_);
    // SDL_DestroyWindow(window); Handled by unique_ptr
}


bool Window::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        engine_->ProccesEvent(&event);

        // Procces events for window
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            return 0;

        case SDL_EVENT_WINDOW_RESIZED:
            UpdateWindowSize();
            break;
        default:
            break;
        }
    }

    return 1;
}

/*
    - Draw
*/
void Window::Clear()
{
    glClearColor( default_clear_color_.r,
                  default_clear_color_.g,
                  default_clear_color_.b,
                  default_clear_color_.a );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(window_.get());
}

/*
    - Properties
*/
Color& Window::GetDefaultClearColor()
{
    return default_clear_color_;
}

void Window::SetDefaultClearColor(Color p_color)
{
    default_clear_color_ = p_color;
}

void Window::UpdateWindowSize()
{
    int w,
        h;
    if (!SDL_GetWindowSizeInPixels(window_.get(), &w, &h))
    {
        SDL_Log("Window is fucked, error while trying get size");
        return;
    }
    width_  = w;
    height_ = h;
    glViewport(0, 0, width_, height_);
}

float Window::GetFramerate()
{
    return io_->Framerate;
}

int Window::GetWidth()
{
    return width_;
}

int Window::GetHeight()
{
    return height_;
}
