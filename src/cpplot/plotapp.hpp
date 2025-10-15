#include "iapp.hpp"
#include "qrlx.hpp"

class PlotApp : public qrlx::IApp
{
  public:
    ~PlotApp() override;

    void Init() override;
    void Start() override;
    void Upadte() override;
    void HandleEvent() override;

    void Render() override;
};