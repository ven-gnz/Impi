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
#include <rendering/core/Renderer.h>
#include <rendering/assets/LineMesh.h>
#include <src/rendering/core/ViewUniforms.h>
#include <imgui.h>

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
	Shader lineShader;
	SphereMesh* spheremesh_ptr = nullptr;
	PlaneMesh* groundmesh_ptr = nullptr;
	LineMesh* linemesh_ptr = nullptr;
	ViewUniform_VPC ViewUniform;

	unsigned int viewUBO = 0;

	std::string name;
	std::vector<Particle> particles;
	std::vector<RenderableParticle> renderables;
	

	virtual void update(float dt);
	virtual void draw(Renderer& renderer, Camera& camera);
	std::string getName() const;

	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);
	virtual void updateMouse(GLFWwindow* window, const Renderer& ren);
	virtual void onActivate();

};