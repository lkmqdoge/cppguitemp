#ifndef QRLX_SHADER
#define QRLX_SHADER

#include <string>

namespace qrlx
{
class Shader 
{
public:
    Shader();
    ~Shader(); // glDeleteShader here
    // void SetUniform(std::string& p_uName);
    bool LoadAndCompile(std::string& p_source);
    void Use();
};
}

#endif
