#ifndef QRLX_SHADER_HPP_
#define QRLX_SHADER_HPP_

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>

namespace qrlx
{
class Shader
{
  public:
    unsigned int ID;
    void Load(const char *vertexPath, const char *fragmentPath);

    void Use();

    void SetBool (const std::string &p_name, bool p_value ) const;
    void SetInt  (const std::string &p_name, int p_value  ) const;
    void SetFloat(const std::string &p_name, float p_value) const;

    void SetVec2(const std::string &p_name, float p_x, float p_y                      ) const;
    void SetVec3(const std::string &p_name, float p_x, float p_y, float p_z           ) const;
    void SetVec4(const std::string &p_name, float p_x, float p_y, float p_z, float p_w) const;

    void SetVec2(const std::string &p_name, const glm::vec2 &p_value) const;
    void SetVec3(const std::string &p_name, const glm::vec3 &p_value) const;
    void SetVec4(const std::string &p_name, const glm::vec4 &p_value) const;

    void SetMat2(const std::string &p_name, const glm::mat2 &p_value) const;
    void SetMat3(const std::string &p_name, const glm::mat3 &p_value) const;
    void SetMat4(const std::string &p_name, const glm::mat4 &p_value) const;

  private:
    void CheckLinkProgramErr  (unsigned int p_program);
    void CheckShaderCompileErr(unsigned int p_shader);
};
} // namespace qrlx

#endif
