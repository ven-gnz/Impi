#pragma once
#include <src/scenes/Scene.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <src/Settings.h>


struct cpuBlob
{
	glm::vec2 pos;
	glm::vec2 vel;
	float radius;
	float mass;
	float pad;
	float pad2;
}; // now its 32 bits exactly, so it matches GPU struct. Good stuff.

class Fluid : public Scene
{

private:


	GLuint computeProgram = 0;
	GLuint ssbo; // shader storage buffer object
	GLuint texture = 0;
	GLuint texVAO = 0;
	int width = windowWidth, height = windowHeight;

public:


	Fluid(Camera &camera);
	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;
};