#include "engine.hpp"
#include "plotapp.hpp"
#include <memory>

using namespace qrlx;

int main(int argc, char** argv)
{
    const std::string title = "cpplot";
    Engine e = Engine(std::make_unique<PlotApp>(), title, 800, 600);

    e.Start();
    e.Run();
    e.Quit();
    return 0;
}
