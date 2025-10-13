#include "engine.hpp"
#include "iapp.hpp"
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

    }
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