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
		Camera& camera,
		const char* vertexPath = nullptr,
		const char* fragmentPath = nullptr,
		const char* geometryPath = nullptr);

	Camera& camera;
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

	void updateViewUniform();
	void upstreamViewUniform() const;
	virtual void update(float dt);
	virtual void draw();
	std::string getName() const;

	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

};