#include "camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float zoom, double sensitivity, float cameraSpeed)
  : _front(glm::vec3(0.f, 0.f, -1.f)), _worldUp(up), _pos(pos), _yaw(yaw), _pitch(pitch), _sensitivity(sensitivity), _cameraSpeed(cameraSpeed)
{
  _zoom = 45.0f;
  updateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
  return glm::lookAt(_pos, _pos + _front, _up);
}

glm::vec3 Camera::GetPosition()
{
  return _pos;
}

void Camera::ProcessKeyboard(CameraDirection dir, float deltaTime)
{
  switch (dir) {
  case CameraDirection::BACK:
    _pos -= _front * deltaTime * _cameraSpeed;
    break;
  case CameraDirection::FOWARD:
    _pos += _front * deltaTime * _cameraSpeed;
    break;
  case CameraDirection::RIGHT:
    _pos += _right * deltaTime * _cameraSpeed;
    break;;
  case CameraDirection::LEFT:
    _pos -= _right * deltaTime * _cameraSpeed;
    break;
  }
  updateVectors();
}

void Camera::ProcessMouseMove(float xoffset, float yoffset)
{
  _pitch += yoffset * _sensitivity;;
  _yaw += xoffset * _sensitivity;;
    
  if (_pitch < -89.f) {
    _pitch = -89.f;
  } else if (_pitch > 89.f) {
    _pitch = 89.f;
  }

  updateVectors();
}

void Camera::ProcessMouseScroll(float offset)
{
  _zoom -= offset;
  if (_zoom < 1.0f)
    _zoom = 1.0f;
  if (_zoom > 60.0f)
    _zoom = 60.0f;
}

void Camera::updateVectors()
{
  glm::vec3 direction;
  direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  direction.y = sin(glm::radians(_pitch));
  direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
 
  _front = glm::normalize(direction);
  _right = glm::normalize(glm::cross(_front, _worldUp));
  _up = glm::normalize(glm::cross(_right, _front));
}

float Camera::GetZoom()
{
  return _zoom;
}
