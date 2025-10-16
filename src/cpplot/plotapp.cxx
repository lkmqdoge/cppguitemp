#include "plotapp.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"


void PlotApp::Init()
{
}

void PlotApp::Start()
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

    // move to separate backend renderer
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
