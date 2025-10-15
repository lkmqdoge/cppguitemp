#ifndef QRLX_IRENDERING_BACKEND
#define QRLX_IRENDERING_BACKEND

namespace qrlx
{
class IRenderingBackend
{
public:
    virtual bool Init() = 0;
    virtual bool InitWindow() = 0;
    
    virtual void Clear() = 0;
    virtual void DrawTexture() = 0;
    virtual void DrawRect() = 0;

    virtual void ImGui_NewFrame() = 0;
    virtual void ImGui_RenderDrawData() = 0;
};
}

#endif
