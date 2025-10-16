#include "plotapp.hpp"
#include "glad/glad.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "log.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

unsigned int VBO, VAO;

unsigned int shaderProgram, vertexShader, fragmentShader;

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
};

static std::string _LoadShader(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        std::cerr << filename << " cant be read\n";
        return {};
    }

    auto size = std::filesystem::file_size(filename);
    std::string res(size, '\0');
    ifs.read(&res[0], size);
    
    return res;
}

static unsigned int _CreateShader(const std::string& source, unsigned int type)
{
    unsigned int shader = glCreateShader(type);

    const char* c = source.c_str();
    glShaderSource(shader, 1, &c, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

void PlotApp::Init()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1 ,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto vsource   = _LoadShader("resources/plot.vert");
    auto fsource   = _LoadShader("resources/plot.frag");
    vertexShader   = _CreateShader(vsource, GL_VERTEX_SHADER);
    fragmentShader = _CreateShader(fsource, GL_FRAGMENT_SHADER);
    
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shaderProgram);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, 0.9f, 0.4f, 0.6f, 1.0f);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PlotApp::Start()
{
    LOG("Hello from Plot app");
}

void PlotApp::Exit()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  
}

void PlotApp::Upadte()
{
}

void PlotApp::HandleEvent()
{
}



void PlotApp::Render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // move to separate backend renderer
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();
    static float f = 0.0f;
    static int counter = 0;
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::Begin("Hello, world!", NULL,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
    ImGui::Text("This is some useful text.");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
