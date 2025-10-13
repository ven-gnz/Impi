#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../src/rendering/core/Shader.h>
#include <rendering/assets/RenderableParticle.h>
#include <../src/rendering/assets/PlaneMesh.h>


class Scene {
public:

	Scene(const std::string name,
		const char* vertexPath = nullptr,
		const char* fragmentPath = nullptr,
		const char* geometryPath = nullptr);
	Shader shader;
	SphereMesh* spheremesh_ptr = nullptr;
	PlaneMesh* groundmesh_ptr = nullptr;
	


	std::string name;
	std::vector<Particle> particles;
	std::vector<RenderableParticle> renderables;
	

	void update(float dt);
	void draw(const glm::mat4& projection, const glm::mat4& view) const;
	std::string getName() const;

	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

};