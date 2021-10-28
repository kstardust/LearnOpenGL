#pragma once

#ifndef __SHADER_H
#define __SHADER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fcntl.h>

class ShaderProg {
    public:        
        ShaderProg(std::string vertex_shader_path, std::string frag_shader_path);
        unsigned int GetProgram();
        bool UseProgram();
        void SetFloat(const std::string &name, float value);
        void SetInt(const std::string &name, int value);                        
    private:
        void Init();
        void ReadFile(std::string file_path, unsigned char **buff);
        void CreateProgram(unsigned int vertex_shader, unsigned int frag_shader);
        unsigned int CreateShader(const char* program, int type);        

        unsigned int m_program_id = 0;
        std::string vertex_shader_path, frag_shader_path;
};

#endif