#include "app.hpp"
#include "SDL3/SDL_timer.h"
#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "shader.hpp"

static unsigned int VBO,
                    VAO;

static glm::vec3 cameraPos = glm::vec3(0.0f);
static glm::vec3 cameraTgt = glm::vec3(1.0f, 0.0f, 0.0f);
static glm::vec3 cameraDir = glm::normalize(cameraPos - cameraTgt);

// Cube
static float vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

static glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

static bool wireframeMode;
static qrlx::Shader plotShader;
static float fov = 45.0f;

void PlotApp::Init()
{
    glGenVertexArrays (1,   &VAO);
    glGenBuffers      (1,   &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    plotShader.Load("resources/plot.vert", "resources/plot.frag");

    // Position attribute
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);
}

void PlotApp::Start()
{
}

void PlotApp::Exit()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void PlotApp::Update()
{

}

void PlotApp::HandleEvent(SDL_Event* p_event)
{
}

void PlotApp::Render()
{
    glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);

    plotShader.Use();

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(fov),
                            (float)MainWindow->GetWidth()/MainWindow->GetHeight(),
                            0.1f,
                            100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    plotShader.SetMat4("projection", proj);
    plotShader.SetMat4("view", view);

    glBindVertexArray(VAO);

    for (int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = i + (float)SDL_GetTicks() / 20;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        plotShader.SetMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // TODO: move to separate backend renderer
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::Begin("GL PLAYGROUND!", NULL,
                  ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("Drawing the plot using OpenGL!");
    ImGui::SliderFloat("float", &fov, 5.0f, 180.0f);
    ImGui::Checkbox("Wireframe Mode", &wireframeMode);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
