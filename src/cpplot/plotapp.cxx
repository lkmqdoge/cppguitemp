#include "plotapp.hpp"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "log.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

static unsigned int VBO,  VAO,  EBO,
                    VBOt, VAOt;

static unsigned int shaderProgram, 
                    shaderProgramT;


static float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

// Triangle
static float tvertices[] = {
    -1.0f, 1.0f, 0.0f,
    -0.5f, 1.0f, 0.0f,
    -1.0f, 0.5f, 0.0f,
};

static unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

static bool wireframeMode;

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
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

void PlotApp::Init()
{
    CLOG("Hi from plot app");

    // Start Rectangle
    glGenBuffers(1 ,&VBO); // rectangle vertex array object
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    unsigned int    vertexShader,
                    fragmentShader,
                    fragmentShaderT;

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

    glUniform4f(vertexColorLocation, 0.9f, 0.4f, 0.6f, 1.0f);

    glVertexAttribPointer(
        0,
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3*sizeof(float), 
        (void*)0
    );
    glEnableVertexAttribArray(0);
    // END Rectangle

    // START triangle
    glGenVertexArrays(1, &VAOt); // triangle vertex array object
    glGenBuffers(1, &VBOt);
    
    glBindVertexArray(VAOt);
    glBindBuffer(GL_ARRAY_BUFFER, VBOt);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tvertices), tvertices, GL_STATIC_DRAW);
    
    auto tfsrc = _LoadShader("resources/tris.frag");
    fragmentShaderT = _CreateShader(tfsrc, GL_FRAGMENT_SHADER);
    shaderProgramT = glCreateProgram();
    glAttachShader(shaderProgramT, vertexShader);
    glAttachShader(shaderProgramT, fragmentShaderT);
    glLinkProgram(shaderProgramT);

    glVertexAttribPointer(
        0,
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3*sizeof(float), 
        (void*)0
    );
    glEnableVertexAttribArray(0);
    // END triangle

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
    glDeleteShader(fragmentShaderT); 
}

void PlotApp::Start()
{
    LOG("Hello from Plot app");
}

void PlotApp::Exit()
{

}

void PlotApp::Upadte()
{
}

void PlotApp::HandleEvent()
{
}

void PlotApp::Render()
{
    glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glUseProgram(shaderProgramT);
    glBindVertexArray(VAOt);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // move to separate backend renderer
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();
    static float f = 0.0f;
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::Begin("GL PLAYGROUND!", NULL,
                  ImGuiWindowFlags_NoResize 
                | ImGuiWindowFlags_NoMove 
                | ImGuiWindowFlags_NoCollapse 
                | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("Drawing the plot using OpenGL!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    // if (ImGui::Button("Button"))
    //     counter++;
    // ImGui::SameLine();
    // ImGui::Text("counter = %d", counter);
    ImGui::Checkbox("Wireframe Mode", &wireframeMode);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
