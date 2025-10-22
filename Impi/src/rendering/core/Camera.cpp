#pragma once

#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	Up = up;
	WorldUp = glm::vec3(Up.x, Up.y, Up.z);
	Yaw = yaw;
	Pitch = pitch;

	updateCameraVectors();
}

Camera::Camera(ViewPort viewPort)
{

	Position = defaultPos;
	Up = defaultUp;
	WorldUp = glm::vec3(Up.x, Up.y, Up.z);
	Yaw = YAW;
	Pitch = PITCH;
	Front = defaultFront;
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;
	Direction = glm::normalize(Position + Front);
	Right = glm::cross(WorldUp, Direction);
	vp = viewPort;

	 near = 0.1f;
	 far = 50.0f;
	 aspect = (float) vp.SCR_WIDTH / (float) vp.SCR_HEIGHT;
	 fov = glm::radians(60.0f);

}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position+Front, Up);
	//return lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjection()
{
	return glm::perspective(fov, aspect, near, far);
}

glm::mat4 Camera::lookAt(glm::vec3 Pos, glm::vec3 Target, glm::vec3 WorldUp) {

	glm::vec3 d = glm::normalize(Pos - Target);
	glm::vec3 r = glm::normalize(glm::cross(glm::normalize(WorldUp), d));
	glm::vec3 u = glm::cross(d, r);

	glm::vec3 p(-Pos.x, -Pos.y, -Pos.z);

	glm::mat4x4 translation = {
	  r.x, u.x, d.x, 0.0,
	  r.y, u.y, d.y, 0.0,
	  r.z, u.z, d.z, 0.0,
	  0.0, 0.0, 0.0, 1.0,
	};

	glm::mat4x4 rotation = {
	  1.0, 0.0, 0.0, 0.0,
	  0.0, 1.0, 0.0, 0.0,
	  0.0, 0.0, 1.0, 0.0,
	  p.x, p.y, p.z, 1.0
	};

	return translation * rotation;

}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD) {
		Position += Front * velocity;
	}
	if (direction == BACKWARD) {
		Position -= Front * velocity;
	}
	if (direction == LEFT) {
		Position -= Right * velocity;
	}
	if (direction == RIGHT) {
		Position += Right * velocity;
	}
	Position.y = 0.0f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {

	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {

		if (Pitch > 89.0f) { Pitch = 89.0f; }
		if (Pitch < -89.0f) { Pitch = -89.0f; }
	}

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

}

glm::vec3 Camera::getPosition()
{
	return this->Position;
}