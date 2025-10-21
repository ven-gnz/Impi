#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera {
public:

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::vec3 Direction;


	static constexpr glm::vec3 defaultPos = glm::vec3(0.0f, 1.0f, 5.0f);
	static constexpr glm::vec3 defaultTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 defaultUp = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr glm::vec3 defaultFront = glm::vec3(0.0f, 0.0f, -1.0f);

	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera();
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	

	glm::mat4 GetViewMatrix();
	glm::mat4 lookAt(glm::vec3 Pos, glm::vec3 Target, glm::vec3 LookAt);
	glm::vec3 getPosition();

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	//void ProcessMouseScroll(float yoffset);



private:
	void updateCameraVectors();

};