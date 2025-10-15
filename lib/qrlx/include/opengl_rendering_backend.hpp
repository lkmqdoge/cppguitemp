#ifndef QRLX_IRENDERING_BACKEND
#define QRLX_IRENDERING_BACKEND

#include "irendering_backend.hpp"

namespace qrlx
{
class OpenGLRenderingBackend : public IRenderingBackend
{
public:
    bool Init() override;
    bool InitWindow() override;
    
    void Clear() override;
    void DrawTexture() override;
    void DrawRect() override;

    void ImGui_NewFrame() override;
    void ImGui_RenderDrawData() override;
};
}

#endif
