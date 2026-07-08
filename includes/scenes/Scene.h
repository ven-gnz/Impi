#pragma once
#include <string>
#include <vector>
#include <opengl/ViewUniforms.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <opengl/Shader.h>
#include <opengl/RenderableParticle.h>
#include <opengl/PlaneMesh.h>
#include <tools/Camera.h>
#include <opengl/Renderer.h>
#include <opengl/LineMesh.h>
#include <imgui.h>
#include <tools/Raycaster.h>
#include <physics/PhysicsWorld.h>

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
	CubeMesh* cubemesh_ptr = nullptr;
	LineMesh* linemesh_ptr = nullptr;
	ViewUniform_VPC ViewUniform;
	Raycaster raycaster;
	PhysicsWorld physicsWorld;

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