#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

glm::mat4 Camera::getViewMatrix() {    
    return glm::lookAt(mCentre + _RelPos, mCentre, _WorldUp);
};

void Camera::orbitCam(float dx, float dy) {
    mYaw += dx * 0.25f;
    mPitch += dy * 0.25f;

    // Prevent pitch from becoming 90deg
    if (mPitch > 89.0f)
        mPitch = 89.0f;
    if (mPitch < -89.0f)
        mPitch = -89.0f;
    _updateCamera();
};

void Camera::translateCam(float dx, float dy) {
    mCentre += (_CamUp * dy + _CamRight * dx) * 0.01f;
    _updateCamera();
};

void Camera::zoomCam(float dr) {
    mRadius -= dr;
    if (mRadius < cMinRadius) 
        mRadius = cMinRadius;
    if (mRadius > cMaxRadius) 
        mRadius = cMaxRadius;
    _updateCamera();
};