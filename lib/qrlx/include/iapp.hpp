#ifndef QRLX_IAPP_HPP_
#define QRLX_IAPP_HPP_

#include "window.hpp"

namespace qrlx
{

class Engine;

class IApp
{
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void HandleEvent() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

    Window* MainWindow;
    Engine* Engine;
};
}

#endif
