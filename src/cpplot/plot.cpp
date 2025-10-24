#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "qrlx.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "imgui.h"
#include "shader.hpp"
#include <cmath>
#include <vector>

namespace plt
{


class PlotApp : public qrlx::IApp
{
public:
    void Init()                           override;
    void Start()                          override;
    void Update()                         override;
    void HandleEvent(SDL_Event* p_event)  override;
    void Render()                         override;
    void Exit()                           override;

    static constexpr float kFSR_Verticies[] = {
        -1.0f,  1.0f, 
         1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f
    };

    static constexpr int kFSR_Indicies[] = {
        0, 1, 2,
        1, 2, 3
    };

private:
    unsigned int VBO_,
                 VAO_,
                 EBO_;
    qrlx::Shader plot_shader_;

    float f_start_  { -100.0f    }, 
          f_end_    {  100.0f    },
          f_step_   {      0.05f };

    std::vector<glm::vec2>  points_;

    bool use_ortho_ { true };
};

}

void plt::PlotApp::Init()
{
    // точки
    auto f = [](float p_x) -> float { return std::sin(p_x); };

    float x = f_start_; 
    while (x < f_end_)
    {
        points_.push_back(glm::vec2(x, (f(x))));
        x+= f_step_;
    }
    
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    glBufferData(GL_ARRAY_BUFFER, sizeof points_.data(), points_.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // 3 f pos
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(float),
        (void*)0
    );

    plot_shader_.Load("resources/plot.vert", "resources/plot.frag");
}

void plt::PlotApp::Start(){}
void plt::PlotApp::HandleEvent(SDL_Event* p_event){}

void plt::PlotApp::Update(){}

void plt::PlotApp::Render()
{
    auto view = glm::mat4(1.0f);
    auto proj = glm::mat4(1.0f);
    if (use_ortho_) {
        proj = glm::ortho(
            0.0f,
            (float)MainWindow->GetWidth(),
            (float)MainWindow->GetHeight(),
            0.0f
        );
    }
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));

    plot_shader_.Use(); 
    plot_shader_.SetMat4("u_projection",  proj   );
    plot_shader_.SetMat4("u_view",        view   );
    plot_shader_.SetMat4("u_model",       model  );
    
    // Draw single graph
    glBindVertexArray(VAO_);
    glLineWidth(40);
    glDrawArrays(GL_LINE_STRIP, 0, points_.size());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("funchii", NULL, ImGuiWindowFlags_NoCollapse
                                  | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("%.3f / %.3f FPS", 1000.0f / MainWindow->GetFramerate(), MainWindow->GetFramerate());
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void plt::PlotApp::Exit()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

int main()
{
    qrlx::Engine e = qrlx::Engine(std::make_unique<plt::PlotApp>(), "plot", 800, 600);
    e.Start();
    e.Run();
    e.Quit();

    return 0;
}
