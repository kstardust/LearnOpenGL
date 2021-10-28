#include <iostream>
#include <math.h>
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
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    
    #endif

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
    #ifdef __APPLE__    
        "/Users/Kevin/Development/OpenGL/Testing/src/vertex.glsl",
        "/Users/Kevin/Development/OpenGL/Testing/src/fragment.glsl"
    #elif defined(WIN32)
        "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\vertex.glsl", 
        "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\fragment.glsl"     
    #endif
    );

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f  // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    unsigned int VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);    

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int ufColorLocation = glGetUniformLocation(shader_prog.GetProgram(), "ufColor");

    while (!glfwWindowShouldClose(window)) 
    {
        process_input(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);    
        glClear(GL_COLOR_BUFFER_BIT);

        shader_prog.UseProgram();
        float green = (sin(glfwGetTime()) / 2.0f + 0.5f);

        glUniform4f(ufColorLocation, 0.0f, green, 0.0f, 1.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
