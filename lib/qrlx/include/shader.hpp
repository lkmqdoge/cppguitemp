#ifndef QRLX_SHADER_HPP
#define QRLX_SHADER_HPP

#include <string>

namespace qrlx
{
class Shader
{
  public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath);

    void Use();

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
};



} // namespace qrlx

#endif
