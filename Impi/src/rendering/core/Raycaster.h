#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <src/math/Vector3.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_projection.hpp>

namespace Impi
{


// https://antongerdelan.net/opengl/raycasting.html
class Raycaster
{
public:
	Vector3 screenToWorld(double xpos, double ypos, real z, GLFWwindow* window, glm::mat4 view, glm::mat4 proj);

};

}