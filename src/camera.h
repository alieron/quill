#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

// Default camera values
const float RADIUS = 5.0f;
const float MINRADIUS = 1.0f;
const float MAXRADIUS = 20.0f;
const float YAW = -90.0f;
const float PITCH = 0.0f;
// const float SPEED = 2.5f;
// const float SENSITIVITY = 0.1f;
// const float ZOOM = 45.0f;

class Camera {
public:
	// Include projection matrix creation?
	// float fov;
	// float aspect;
	// float near;
	// float far;
	// glm::mat4 getProjectionMatrix();

	// Cam 
	glm::vec3 mCentre;
	float mRadius;
	float cMinRadius;
	float cMaxRadius;
	// Spherical Angles
	float mYaw;
	float mPitch;

	// Constructors
	Camera(glm::vec3 centre = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float radius = RADIUS, float yaw = YAW, float pitch = PITCH) : cMinRadius(MINRADIUS), cMaxRadius(MAXRADIUS) {
		mCentre = centre;
		mRadius = radius;
		_WorldUp = up;
		mYaw = yaw;
		mPitch = pitch;
		_updateCamera();
	};
	
	// Camera(float cenX = 0.0f, float cenY = 0.0f, float cenZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float radius = RADIUS, float yaw = YAW, float pitch = PITCH) : cMinRadius(MINRADIUS), cMaxRadius(MAXRADIUS) {
	// 	mCentre = glm::vec3(cenX, cenY, cenZ);
	// 	mRadius = radius;
	// 	_WorldUp = glm::vec3(upX, upY, upZ);
	// 	mYaw = yaw;
	// 	mPitch = pitch;
	// 	_updateCamera();
	// }

	glm::mat4 getViewMatrix();
	void orbitCam(float dx, float dy);
	void translateCam(float dx, float dy);
	void zoomCam(float dr);

private:
	glm::vec3 _WorldUp;
	glm::vec3 _RelPos;
	glm::vec3 _CamUp;
	glm::vec3 _CamRight;

	void _updateCamera() {
		_RelPos.x = mRadius * cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		_RelPos.y = mRadius * sin(glm::radians(mPitch));
		_RelPos.z = -mRadius * sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		// Ensure that Right and Up are normalised for camera translation
		// _CamRight = glm::normalize(glm::cross(_CamFront, _WorldUp));
		// _CamUp = glm::normalize(glm::cross(_CamRight, _CamFront));
		_CamRight = glm::normalize(glm::cross(_WorldUp, _RelPos));
		_CamUp = glm::normalize(glm::cross(_RelPos, _CamRight));
	};
};


// #include <vector>

// // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
// enum Camera_Movement {
// 	FORWARD,
// 	BACKWARD,
// 	LEFT,
// 	RIGHT
// };



// // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
// class Camera {
// public:
// 	// camera Attributes
// 	glm::vec3 Position;
// 	glm::vec3 Front;
// 	glm::vec3 Up;
// 	glm::vec3 Right;
// 	glm::vec3 WorldUp;
// 	// euler Angles
// 	float Yaw;
// 	float Pitch;
// 	// camera options
// 	float MovementSpeed;
// 	float MouseSensitivity;
// 	float Zoom;

// 	// constructor with vectors
// 	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
// 	{
// 		Position = position;
// 		WorldUp = up;
// 		Yaw = yaw;
// 		Pitch = pitch;
// 		updateCameraVectors();
// 	}
// 	// constructor with scalar values
// 	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
// 	{
// 		Position = glm::vec3(posX, posY, posZ);
// 		WorldUp = glm::vec3(upX, upY, upZ);
// 		Yaw = yaw;
// 		Pitch = pitch;
// 		updateCameraVectors();
// 	}

// 	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
// 	glm::mat4 GetViewMatrix()
// 	{
// 		return glm::lookAt(Position, Position + Front, Up);
// 	}

// 	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
// 	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
// 	{
// 		float velocity = MovementSpeed * deltaTime;
// 		if (direction == FORWARD)
// 			Position += Front * velocity;
// 		if (direction == BACKWARD)
// 			Position -= Front * velocity;
// 		if (direction == LEFT)
// 			Position -= Right * velocity;
// 		if (direction == RIGHT)
// 			Position += Right * velocity;

// 		// Position.y = 0.0f;
// 	}

// 	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
// 	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
// 	{
// 		xoffset *= MouseSensitivity;
// 		yoffset *= MouseSensitivity;

// 		Yaw += xoffset;
// 		Pitch += yoffset;

// 		// make sure that when pitch is out of bounds, screen doesn't get flipped
// 		if (constrainPitch)
// 		{
// 			if (Pitch > 89.0f)
// 				Pitch = 89.0f;
// 			if (Pitch < -89.0f)
// 				Pitch = -89.0f;
// 		}

// 		// update Front, Right and Up Vectors using the updated Euler angles
// 		updateCameraVectors();
// 	}

// 	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
// 	void ProcessMouseScroll(float yoffset)
// 	{
// 		Zoom -= (float)yoffset;
// 		if (Zoom < 1.0f)
// 			Zoom = 1.0f;
// 		if (Zoom > 45.0f)
// 			Zoom = 45.0f;
// 	}

// private:
// 	// calculates the front vector from the Camera's (updated) Euler Angles
// 	void updateCameraVectors()
// 	{
// 		// calculate the new Front vector
// 		glm::vec3 front = glm::vec3(1.0f);
// 		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
// 		front.y = sin(glm::radians(Pitch));
// 		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
// 		Front = glm::normalize(front);
// 		// also re-calculate the Right and Up vector
// 		Right = glm::normalize(glm::cross(Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
// 		Up = glm::normalize(glm::cross(Right, Front));
// 	}
// };