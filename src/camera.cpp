#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera(glm::vec3 centre, glm::vec3 up, float radius, float yaw,
               float pitch) {
  mCentre = centre;
  mRadius = radius;
  cWorldUp = up;
  mYaw = yaw;
  mPitch = pitch;
  updateCamera();
};

void Camera::updateCamera() {
  mRelPos.x = mRadius * cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
  mRelPos.y = mRadius * sin(glm::radians(mPitch));
  mRelPos.z = -mRadius * sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
  // Ensure that Right and Up are normalised for camera translation
  mCamRight = glm::normalize(glm::cross(cWorldUp, mRelPos));
  mCamUp = glm::normalize(glm::cross(mRelPos, mCamRight));
};

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(mCentre + mRelPos, mCentre, cWorldUp);
};

void Camera::orbitCam(float dx, float dy) {
  mYaw += dx * 0.25f;
  mPitch += dy * 0.25f;

  // Prevent pitch from becoming 90deg
  if (mPitch > 89.0f)
    mPitch = 89.0f;
  if (mPitch < -89.0f)
    mPitch = -89.0f;
  updateCamera();
};

void Camera::translateCam(float dx, float dy) {
  mCentre += (mCamUp * dy + mCamRight * dx) * 0.01f;
  updateCamera();
};

void Camera::zoomCam(float dr) {
  mRadius -= dr;
  if (mRadius < MINRADIUS)
    mRadius = MINRADIUS;
  if (mRadius > MAXRADIUS)
    mRadius = MAXRADIUS;
  updateCamera();
};

void Camera::centreAt(glm::vec3 centre) {
	mCentre = centre;
};
