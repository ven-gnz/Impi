#pragma once
#include <glm/glm.hpp>
#include <src/rendering/core/ViewUniforms.h>
#include <glad/glad.h>

class Renderer
{
public:
	Renderer();
	GLuint getViewUBO() const { return viewUBO; }
	void setUniform(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos);
	void view_UBO_Debug_Data() const;

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

private:
	ViewUniform_VPC ViewUniform;
	void initUBO();
	GLuint viewUBO;
};