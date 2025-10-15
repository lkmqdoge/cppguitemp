#include "engine.hpp"
#include "iapp.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "qrlx.hpp"
#include <memory>

using namespace qrlx;

class PlotApp : public IApp
{
public:
    void Init() override
    {
        
    }

    void Start() override
    {

    }

    void Upadte() override
    {

    }

    void HandleEvent() override
    {

    }

    void Render() override
    {
      // move to separate backend renderer
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL3_NewFrame();

      ImGui::NewFrame();
      static float f = 0.0f;
      static int counter = 0;
      ImGui::SetNextWindowPos(ImVec2());
      ImGui::Begin("Hello, world!", NULL, ImGuiWindowFlags_NoResize 
                                        | ImGuiWindowFlags_NoMove
                                        | ImGuiWindowFlags_NoCollapse 
                                        | ImGuiWindowFlags_NoSavedSettings);
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
private:

};

int main()
{
    const std::string title = "cpplot";
    Engine e = Engine(std::make_unique<PlotApp>(), title, 800, 600);

    e.Start();
    e.Run();
    e.Quit();
    return 0;
}
