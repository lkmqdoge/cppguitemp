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

Window::Window(std::string p_title)
    : title(std::move(p_title))
{

}

Window::~Window()
{
    
}

std::unique_ptr<Window> Window::Create(const std::string &p_title)
{
    return std::make_unique<Window>(p_title);
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

    window = std::unique_ptr<SDL_Window, SdlWindowDestroyer>(
        SDL_CreateWindow(title.c_str(), p_width, p_height, flags));
    if (!window)
    {
        LOG("Can't Initialize Widnow!") << SDL_GetError();
        return false;
    }

    context = SDL_GL_CreateContext(window.get());
    if (!context)
    {
        LOG("Can't Create GL Context!") << SDL_GetError();
        return false;
    }

    SDL_GL_MakeCurrent(window.get(), context);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        LOG("Failed to initialize GLAD");
        return false;
    }

    SDL_SetWindowPosition(window.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window.get());


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->IniFilename = NULL;
    io->LogFilename = NULL;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(window.get(), context);
    ImGui_ImplOpenGL3_Init(); 

    return true;
}

void Window::Clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DestroyContext(context);
    // SDL_DestroyWindow(window); Handled by unique_ptr
}


bool Window::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        switch (event.type)
        {
        case SDL_EVENT_QUIT:
          return 0;
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
    glClearColor( defaultClearColor.r,
                  defaultClearColor.g,
                  defaultClearColor.b,
                  defaultClearColor.a );
    glClear(GL_COLOR_BUFFER_BIT);

}


void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(window.get());
}

/*
    - Properties
*/
Color& Window::GetDefaultClearColor()
{
    return defaultClearColor;
}

void Window::SetDefaultClearColor(Color p_color)
{
    defaultClearColor = p_color;
}
