#pragma once
#include <glm/glm.hpp>

struct ViewUniform_VPC {
	glm::mat4 view;
	glm::mat4 projection;
	alignas(16) glm::vec3 cameraPos;
	float padding;
};