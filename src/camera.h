#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

// Default camera values
const float RADIUS = 5.0f;
const float MINRADIUS = 1.0f;
const float MAXRADIUS = 20.0f;
const float YAW = 135.0f;  //-90.0f;
const float PITCH = 45.0f; // 0.0f;

class Camera {
private:
  // World
  glm::vec3 cWorldUp;

  // Camera
  glm::vec3 mCentre;
  float mRadius;
  glm::vec3 mRelPos;
  glm::vec3 mCamUp;
  glm::vec3 mCamRight;

  // Spherical Angles
  float mYaw;
  float mPitch;

  void updateCamera();

public:
  // Camera(glm::vec3 centre, glm::vec3 up, float radius, float yaw, float
  // pitch);
  Camera(glm::vec3 centre = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float radius = RADIUS,
         float yaw = YAW, float pitch = PITCH);

  glm::mat4 getViewMatrix();

  // Movements
  void orbitCam(float dx, float dy);
  void translateCam(float dx, float dy);
  void zoomCam(float dr);
	void centreAt(glm::vec3 centre);
};
