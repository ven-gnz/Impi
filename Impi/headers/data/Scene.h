#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <rendering/assets/RenderableParticle.h>

class Scene {
public:

	Scene(const std::string name);

	std::string name;
	std::vector<RenderableParticle> particles;

	void update(float dt);
	void draw(unsigned int shaderProgram) const;
	std::string getName() const;

	void onMouseButton(GLFWwindow* window, int button, int action, int mods);

};