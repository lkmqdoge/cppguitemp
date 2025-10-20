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
    void Quit ();

    void RequestClose();
    void ProccesEvent(SDL_Event* event);

  private:

    bool isRunning_ { 1 };
    uint32_t deltaTime_;

    std::string title_;

    std::unique_ptr<Window> window_ {nullptr};
    std::unique_ptr<IApp> app_;
};
} // namespace qrlx

#endif
