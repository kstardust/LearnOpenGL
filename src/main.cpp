#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_prog.h"
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int Width = 800;
const int Height = 600;

double xMousePos = Width / 2.f;
double yMousePos = Height / 2.f;
bool firstMouse = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightColor(1.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  if (firstMouse) {
    xMousePos = xpos;
    yMousePos = ypos;
    firstMouse = false;    
  }

  float xoffset = xpos - xMousePos;
  float yoffset = yMousePos - ypos;
  xMousePos = xpos;
  yMousePos = ypos;    

  camera.ProcessMouseMove(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}  

void process_input(GLFWwindow *window, float deltaTime)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  CameraDirection dir = CameraDirection::None;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    dir = CameraDirection::FOWARD;
  } else

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    dir = CameraDirection::BACK;
  } 

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    dir = CameraDirection::LEFT;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    dir = CameraDirection::RIGHT;    
  }

  if (dir != CameraDirection::None) {
    camera.ProcessKeyboard(dir, deltaTime);
  }
}

int main()
{
  stbi_set_flip_vertically_on_load(true);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  GLFWwindow* window = glfwCreateWindow(Width, Height, "testing", nullptr, nullptr);
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

  glViewport(0, 0, Width, Height);  

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetCursorPosCallback(window, mouse_callback);

  ShaderProg shader_prog(
  #ifdef __APPLE__  
    "/Users/Kevin/Development/OpenGL/Testing/src/vertex.glsl",
    "/Users/Kevin/Development/OpenGL/Testing/src/fragment.glsl"
  #elif defined(WIN32)
    "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\vertex.glsl", 
    "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\fragment.glsl"   
  #endif
  );

   ShaderProg light_shader(
    #ifdef __APPLE__
      "/Users/Kevin/Development/OpenGL/Testing/src/light_vertex.glsl",
      "/Users/Kevin/Development/OpenGL/Testing/src/light_fragment.glsl"
    #elif defined(WIN32)
      "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\light_vertex.glsl",
      "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\src\\light_fragment.glsl"
    #endif
  );

  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f    
  };

  float border_color[] = {
    1.0f, 1.0f, 0.0f, 1.0f
  };

  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int ligthVAO;
  glGenVertexArrays(1, &ligthVAO);

  glBindVertexArray(ligthVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  // glEnableVertexAttribArray(2);

  std::string texture_dir = 
  #ifdef __APPLE__
    "/Users/Kevin/Development/OpenGL/Testing/textures/";
  #elif defined(WIN32)
    "c:\\Users\\liqilong\\Desktop\\OpenGL\\Testing\\textures\\";
  #endif

  int width, height, n_channels;
  
  unsigned int texture, texture2;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  std::string texture_path = texture_dir + "container.jpeg";
  unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &n_channels, 0);

  if (data == nullptr) {
    std::cerr << "cannot load texture: " << texture_path << std::endl;
  } else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);
  
  texture_path = texture_dir + "awesomeface.png";
  data = stbi_load(texture_path.c_str(), &width, &height, &n_channels, 0);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  if (data == nullptr) {
    std::cerr << "cannot load texture: " << texture_path << std::endl;
  } else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }  

  stbi_image_free(data);
 
  int ufColorLocation = glGetUniformLocation(shader_prog.GetProgram(), "ufColor");
  shader_prog.UseProgram();
  shader_prog.SetInt("ufTexture", 0);  
  shader_prog.SetInt("ufTexture2", 1);

  shader_prog.SetVec3f("lightColor", lightColor);
  shader_prog.SetVec3f("objColor", glm::vec3(1.0f, 0.5f, 0.31f));

  glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  shader_prog.SetMat4("model", model);

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
  };
  
  float lastFrame = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    float now = glfwGetTime();
    float delta = now - lastFrame;
    lastFrame = now;
    process_input(window, delta);    

    shader_prog.UseProgram();
    shader_prog.SetMat4("view", camera.GetViewMatrix());
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 800.0f/600.0f, 1.0f, 100.0f);
    shader_prog.SetMat4("projection", projection);

    light_shader.UseProgram();
    light_shader.SetMat4("view", camera.GetViewMatrix());
    light_shader.SetMat4("projection", projection);
    light_shader.SetVec3f("lightColor", lightColor);
  
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    shader_prog.UseProgram();
    float green = (sin(glfwGetTime()) / 2.0f + 0.5f);

    glUniform4f(ufColorLocation, 0.0f, green, 0.0f, 1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
     
    glBindVertexArray(VAO);

    for (const auto &p : cubePositions) {
      auto trans = glm::translate(glm::mat4(1.0f), p);
      trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.3f, 1.0f));
      shader_prog.SetMat4("model", trans);
      // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    light_shader.UseProgram();
    light_shader.SetMat4("model", glm::scale(glm::translate(glm::mat4(1.0), lightPos), glm::vec3(0.2f)));
    glBindVertexArray(ligthVAO);    
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();

#ifdef __APPLE__
    // https://github.com/glfw/glfw/issues/1334
    static bool macMoved = false;

    if(!macMoved) {
      int x, y;
      glfwGetWindowPos(window, &x, &y);
      glfwSetWindowPos(window, ++x, y);
      macMoved = true;
    }
#endif
    
  }
  glfwTerminate();
  return 0;
}
