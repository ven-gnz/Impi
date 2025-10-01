#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../src/rendering/core/Shader.h>
#include <rendering/assets/RenderableParticle.h>

class Scene {
public:

	Scene(const std::string name);
	Shader shader;

	std::string name;
	std::vector<RenderableParticle> particles;

	void update(float dt);
	void draw() const;
	std::string getName() const;

	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

};