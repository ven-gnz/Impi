#include "Renderer.h"
#include <rendering/core/ViewUniforms.h>
#include <iostream>

Renderer::Renderer() {
    initUBO();
}

void Renderer::initUBO()
{
	glGenBuffers(1, &viewUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewUniform_VPC), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, viewUBO);

}

void Renderer::setUniform(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos)
{
    
    ViewUniform.view = view;
	ViewUniform.projection = projection;
	ViewUniform.cameraPos = cameraPos;
	ViewUniform.padding = 0.0f;

    glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ViewUniform_VPC), &ViewUniform);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::view_UBO_Debug_Data() const
{
	std::cout << "=== view ===" << std::endl;
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			std::cout << "view[" << row << "][" << col << "] = "
				<< ViewUniform.view[col][row] << std::endl;
		}
	}

	std::cout << "=== projection ===" << std::endl;
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			std::cout << "projection[" << row << "][" << col << "] = "
				<< ViewUniform.projection[col][row] << std::endl;
		}
	}

	std::cout << "=== camera position ===" << std::endl;
	std::cout << "cameraPos.x = " << ViewUniform.cameraPos.x << std::endl;
	std::cout << "cameraPos.y = " << ViewUniform.cameraPos.y << std::endl;
	std::cout << "cameraPos.z = " << ViewUniform.cameraPos.z << std::endl;
}

glm::mat4 Renderer::getView() const
{
	return ViewUniform.view;
}
glm::mat4 Renderer::getProjection() const
{
	return ViewUniform.projection;
}