#ifndef APP_HPP
#define APP_HPP

namespace qrlx
{
class App
{
public:
    App();
    ~App();

    void Run();
    void RequestClost();

private:
    void Init();    
    void Update();
    void Quit();
};
}

#endif