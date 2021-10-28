#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_prog.h"

ShaderProg::ShaderProg(std::string vertex_shader_path, std::string frag_shader_path)
    :vertex_shader_path(vertex_shader_path), frag_shader_path(frag_shader_path)
{
    Init();
}

void ShaderProg::Init()
{
    unsigned char *content;
    ReadFile(vertex_shader_path, &content);
    if (content == nullptr)
    {
        exit(-1);
    }
    auto vertex_shader = CreateShader((const char*)content, GL_VERTEX_SHADER);
    free(content);

    ReadFile(frag_shader_path, &content);
    if (content == nullptr)
    {
        exit(-1);
    }

    auto frag_shader = CreateShader((const char*)content, GL_FRAGMENT_SHADER);
    free(content);

    CreateProgram(vertex_shader, frag_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
}

unsigned int ShaderProg::CreateShader(const char* program, int type)
{
    unsigned int vertexShader = glCreateShader(type);
    glShaderSource(vertexShader, 1, &program, nullptr);
    glCompileShader(vertexShader);

    int success;
    char info_log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, info_log);
        std::string shader_type((type == GL_VERTEX_SHADER) ? "VERTEX::" : "FRAGMENT::");
        std::cout << "ERROR:SHADER::" << shader_type << ": " << info_log << std::endl;
    }
    return vertexShader;
}

void ShaderProg::CreateProgram(unsigned int vertex_shader, unsigned int frag_shader)
{
    auto program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader);
    glAttachShader(program_id, frag_shader);
    glLinkProgram(program_id);

    int success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(program_id, 512, nullptr, info_log);        
        std::cerr << "ERROR::SHADER::LINK::" << info_log << std::endl;
        return;
    }
    m_program_id = program_id;
}

void ShaderProg::ReadFile(std::string file_path, unsigned char **buff)
{
    *buff = (unsigned char*)malloc(4096);
    FILE* file = fopen(file_path.c_str(), "r");
    if (file == nullptr) 
    {
        perror("cannot open file");
        *buff = nullptr;
        return;
    }

    size_t n = fread(*buff, 1, 4096, file);
    if (n <= 0) 
    {
        free(*buff);
        *buff = nullptr;
        perror("cannot read file");
        fclose(file);
        return;
    }

    (*buff)[n] = 0;
    fclose(file);
    return;
}

unsigned int ShaderProg::GetProgram()
{
    return m_program_id;
}

bool ShaderProg::UseProgram()
{
    if (m_program_id <= 0) 
    {
        std::cerr << "shader program is not ready" << std::endl;
        return false;
    }
    glUseProgram(m_program_id);
    return true;
}

void ShaderProg::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void ShaderProg::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), value);
}