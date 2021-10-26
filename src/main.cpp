#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_prog.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "testing", nullptr, nullptr);
    if (window == nullptr) 
    {   
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ShaderProg shader_prog(
    #ifdef APPLE    
        "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\vertex.glsl", 
        "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\fragment.glsl"    
    #elif defined(WIN32)
        "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\vertex.glsl", 
        "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\fragment.glsl"     
    #endif
    );

    while (!glfwWindowShouldClose(window)) 
    {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);    
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}