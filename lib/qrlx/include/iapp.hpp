#ifndef QRLX_IAPP_HPP
#define QRLX_IAPP_HPP

namespace qrlx
{
class Engine;

class IApp
{
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Upadte() = 0;
    virtual void HandleEvent() = 0;
    virtual void Render() = 0;
    
    Engine* Engine;
};
}

#endif
