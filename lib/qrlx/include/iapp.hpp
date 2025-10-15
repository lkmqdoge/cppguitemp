#ifndef QRLX_
#define QRLX_

namespace qrlx
{
class IApp
{
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Upadte() = 0;
    virtual void HandleEvent() = 0;
    virtual void Render() = 0;
};
}

#endif