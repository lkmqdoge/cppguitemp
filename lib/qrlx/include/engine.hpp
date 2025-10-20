#ifndef QRLX_ENGINE_HPP_
#define QRLX_ENGINE_HPP_

#include <memory>
#include <string>

#include "iapp.hpp"
#include "window.hpp"

namespace qrlx
{
class Engine
{
  public:
    Engine(std::unique_ptr<IApp>&& p_app, std::string p_title, int p_screenWidth, int p_screenHight);

    void Start();
    void Run();
    void Quit();

    void RequestClose();

  private:

    bool isRunning { 1 };
    uint32_t deltaTime;

    std::string title;

    std::unique_ptr<Window> window{nullptr};
    std::unique_ptr<IApp> app;
};
} // namespace qrlx

#endif
