#include "shader.hpp"
#include <fstream>
#include <string>

using namespace qrlx;

Shader::Shader()
{

}

Shader::~Shader()
{

}

bool Shader::LoadAndCompile(std::string& p_source)
{
    std::string shaderSource; 
    std::fstream f;
    f.open(p_source);
    
    // shaderSource = f.get();
    
    return true; 
}
