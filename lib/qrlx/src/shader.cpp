#include "shader.hpp"

#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace qrlx;

void Shader::Load(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try 
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, 
                          fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        vShaderFile.close();
        fShaderFile.close();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    CheckShaderCompileErr(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    CheckShaderCompileErr(fragment);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    CheckLinkProgramErr(ID);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetBool(const std::string &p_name, bool p_value) const
{         
    glUniform1i(glGetUniformLocation(ID, p_name.c_str()), (int)p_value); 
}

void Shader::SetInt(const std::string &p_name, int p_value) const
{ 
    glUniform1i(glGetUniformLocation(ID, p_name.c_str()), p_value); 
}

void Shader::SetFloat(const std::string &p_name, float p_value) const
{ 
    glUniform1f(glGetUniformLocation(ID, p_name.c_str()), p_value); 
}


/*
    Vector
*/
void Shader::SetVec2(const std::string &p_name, const glm::vec2 &p_value) const
{
    glUniform2fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]); 
}

void Shader::SetVec3(const std::string &p_name, const glm::vec3 &p_value) const
{
    glUniform3fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]); 
}

void Shader::SetVec4(const std::string &p_name, const glm::vec4 &p_value) const
{
    glUniform4fv(glGetUniformLocation(ID, p_name.c_str()), 1, &p_value[0]); 
}

void Shader::SetVec2(const std::string &p_name, float p_x, float p_y) const
{
    glUniform2f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y); 
}

void Shader::SetVec3(const std::string &p_name, float p_x, float p_y, float p_z) const
{
    glUniform3f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y, p_z); 
}

void Shader::SetVec4(const std::string &p_name, float p_x, float p_y, float p_z, float p_w) const
{
    glUniform4f(glGetUniformLocation(ID, p_name.c_str()), p_x, p_y, p_z, p_w); 
}


/*
    Matrix
*/
void Shader::SetMat2(const std::string &p_name, const glm::mat2 &p_value) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
}

void Shader::SetMat3(const std::string &p_name, const glm::mat3 &p_value) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
}

void Shader::SetMat4(const std::string &p_name, const glm::mat4 &p_value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, p_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
}


/*
    Check errors
*/
void Shader::CheckLinkProgramErr(unsigned int p_program)
{
    GLint success;
    GLchar infoLog[1024];

    glGetProgramiv(p_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(p_program, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR" << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

void Shader::CheckShaderCompileErr(unsigned int p_shader)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(p_shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type" << "\n"
                  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}