#pragma once
#include <string>
#include <vector>
#include <rendering/core/ViewUniforms.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <rendering/core/Shader.h>
#include <rendering/assets/RenderableParticle.h>
#include <rendering/assets/PlaneMesh.h>
#include <rendering/core/Camera.h>

class Scene {
public:

	Scene(const std::string name,
		Camera camera,
		const char* vertexPath = nullptr,
		const char* fragmentPath = nullptr,
		const char* geometryPath = nullptr);
	Shader shader;
	Shader groundShader;
	SphereMesh* spheremesh_ptr = nullptr;
	PlaneMesh* groundmesh_ptr = nullptr;
	ViewUniform_VPC ViewUniform;

	unsigned int viewUBO = 0;

	std::string name;
	std::vector<Particle> particles;
	std::vector<RenderableParticle> renderables;
	void initUBO();
	void view_UBO_Debug_Data() const;
	void updateUBO(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos) const;

	void updateViewUniform(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos);
	void upstreamViewUniform() const;
	void update(float dt);
	void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cameraPos);
	std::string getName() const;

	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

};