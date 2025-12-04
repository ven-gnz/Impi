#pragma once
#include <src/scenes/Scene.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Fluid : public Scene
{

private:


	GLuint computeProgram = 0;
	GLuint texture = 0;
	GLuint texVAO = 0;
	int width = 512, height = 512;

public:


	Fluid(Camera &camera);
	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;
};