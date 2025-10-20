#ifndef QRLX_VECTOR2F_HPP_
#define QRLX_VECTOR2F_HPP_

namespace qrlx
{
struct Vector2f
{
    float x, y;
    Vector2f();
    Vector2f(float x, float y)
        : x(x), y(y) {}
};
}

#endif
