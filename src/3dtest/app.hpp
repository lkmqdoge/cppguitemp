#include "qrlx.hpp"

class PlotApp : public qrlx::IApp
{
  public:
    void Init() override;
    void Start() override;
    void Update() override;
    void HandleEvent() override;
    void Render() override;
    void Exit() override;
};
