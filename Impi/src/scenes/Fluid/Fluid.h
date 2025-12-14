#pragma once
#include <src/scenes/Scene.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <src/Settings.h>


struct cpuBlob
{
	glm::vec4 pos;
	glm::vec4 vel;
	glm::vec4 properties;
}; // now its 32 bits exactly, so it matches GPU struct. Good stuff.

struct GPUBox
{
	glm::mat4 model;
	glm::mat4 modelInverse;
	glm::vec4 halfSize;
	CubeMesh* mesh_ptr;
	glm::vec2 pad;
	
};

class Fluid : public Scene
{

private:


	GLuint computeProgram = 0;
	GLuint ssbo; // shader storage buffer object
	GLuint texture = 0;
	GLuint texVAO = 0;
	GLuint containerSSBO;
	int width = windowWidth, height = windowHeight;
	GPUBox boundingBox;
	Shader fluidComputeRenderShader;
	CubeMesh boundingVolumeMesh;
	unsigned int numBlobs = 2;

public:


	Fluid(Camera &camera);
	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;
};