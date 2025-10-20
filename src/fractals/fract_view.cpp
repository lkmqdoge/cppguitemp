#include "SDL3/SDL_events.h"
#include "glad/glad.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "engine.hpp"
#include "iapp.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "shader.hpp"
#include "window.hpp"
#include <memory>

namespace frc
{

enum class CurrentFract
{
    MandelBrot_Set,
    Sierpinski_Carpet
};

class FractView : public qrlx::IApp
{
public:
    void Init()                             override;
    void Start()                            override;
    void Update()                           override;
    void Render()                           override;
    void Exit()                             override;
    void HandleEvent(SDL_Event* p_event)    override;

    static constexpr float kFSR_Verticies[] = {
        1.0f,  1.0f, 0.0f,  // top right
        1.0f, -1.0f, 0.0f,  // bottom right
       -1.0f, -1.0f, 0.0f,  // bottom left
       -1.0f,  1.0f, 0.0f   // top left
    };

    static constexpr int kFSR_Indicies[] = {
        0, 1, 3,
        1, 2, 3
    };

private:
    qrlx::Shader mandelBrotShader_;
    unsigned int FSR_VBO_,
                 FSR_VAO_,
                 FSR_EBO_;

    float mandelbrotZoomSize = 1.0f;
    glm::vec2 mandelbrotZoomCenter = glm::vec2(1.0f);
};
}

void frc::FractView::Init()
{
    glGenVertexArrays(1, &FSR_VAO_);
    glGenBuffers     (1, &FSR_VBO_);
    glGenBuffers     (1, &FSR_EBO_);

    glBindVertexArray(FSR_VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, FSR_VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kFSR_Verticies), kFSR_Verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FSR_EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kFSR_Indicies), kFSR_Indicies, GL_STATIC_DRAW);

    mandelBrotShader_.Load("resources/mandelbrot.vert", "resources/mandelbrot.frag");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void frc::FractView::Start(){}
void frc::FractView::Update(){}

void frc::FractView::HandleEvent(SDL_Event* p_event)
{
    if (p_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {

    }
}

void frc::FractView::Exit()
{
    glDeleteVertexArrays(1, &FSR_VAO_);
    glDeleteBuffers     (1, &FSR_VBO_);
    glDeleteBuffers     (1, &FSR_EBO_);
}

void frc::FractView::Render()
{
    mandelBrotShader_.SetVec2("iResolution",
                              MainWindow->GetWidth(),
                              MainWindow->GetHeight());
    mandelBrotShader_.SetFloat("u_zoomSize",  mandelbrotZoomSize);
    mandelBrotShader_.SetVec2("u_zoomCenter", mandelbrotZoomCenter);

    mandelBrotShader_.Use();
    glBindVertexArray(FSR_VAO_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // TODO: move to separate backend renderer
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::SetNextWindowSize(ImVec2(200, 160));
    ImGui::Begin("Fractals!", NULL, ImGuiWindowFlags_NoCollapse
                                  | ImGuiWindowFlags_NoSavedSettings);
    ImGui::SliderFloat("Zoom", &mandelbrotZoomSize, 0.001f, 10.0f);

    ImGui::SliderFloat("Zoom Center x", &mandelbrotZoomCenter.x, 0.01f, 10.0f);
    ImGui::SliderFloat("Zoom Center y", &mandelbrotZoomCenter.y, 0.01f, 10.0f);
    ImGui::Text("%.3f / %.3f FPS", 1000.0f / MainWindow->GetFramerate(), MainWindow->GetFramerate());


    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
    const std::string title = "fractView";
    qrlx::Engine e = qrlx::Engine(std::make_unique<frc::FractView>(), title, 800, 600);

    e.Start();
    e.Run();
    e.Quit();
    return 0;
}
