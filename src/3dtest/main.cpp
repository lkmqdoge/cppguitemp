#include "engine.hpp"
#include "app.hpp"
#include <memory>

int main()
{
    const std::string title = "cubiki";
    qrlx::Engine e = qrlx::Engine(std::make_unique<PlotApp>(), title, 800, 600);

    e.Start();
    e.Run();
    e.Quit();
    return 0;
}
