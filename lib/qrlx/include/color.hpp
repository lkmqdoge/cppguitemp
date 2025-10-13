#ifndef QRLX_COLOR_HPP
#define QRLX_COLOR_HPP

namespace qrlx
{
typedef struct Color
{
    float r, g, b, a;
    Color() = default;
    Color(float p_r, float p_g, float p_b, float p_a = 1.0f);
} Color;
} // namespace qrlx

#endif