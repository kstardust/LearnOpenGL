#pragma once

#ifndef __CAMERA_H
#define  __CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const double Fov = 45.0f;
const float Yaw = -90.f;
const float Pitch = 0;
const float CursorSensitivity = .1f;
const float CameraSpeed = 2.0f;

enum class CameraDirection {
  FOWARD,
    BACK,
    LEFT,
    RIGHT,
    None,
};

class Camera {
public:
  Camera(glm::vec3 pos, glm::vec3 up, float yaw=Yaw, float pitch=Pitch, float zoom=Fov, double sensitivity=CursorSensitivity, float cameraSpeed=CameraSpeed);
  glm::mat4 GetViewMatrix();
  float GetZoom();
  void ProcessMouseScroll(float offset);
  void ProcessMouseMove(float xoffset, float yoffset);
  void ProcessKeyboard(CameraDirection, float deltaTime);    
  glm::vec3 GetPosition();
 private:
  glm::vec3 _front;
  glm::vec3 _worldUp;
  glm::vec3 _up;  
  glm::vec3 _pos;
  glm::vec3 _right;
  
  float _yaw;
  float _pitch;
  float _zoom;
  float _sensitivity;    
  float _cameraSpeed;
  
  void updateVectors();
};

#endif
