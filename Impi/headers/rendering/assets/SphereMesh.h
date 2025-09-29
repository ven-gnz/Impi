#pragma once
#include <vector>
#include <glad/gl.h>
#include <glm/glm.hpp>

/*
https://songho.ca/opengl/gl_sphere.html
Origokeskeinen yksikköpallo. 
Resurssi yllä. 
Tavoitteena tarjota sama utiliteetti kuin glutsolidsphere.
*/ 

struct SphereMesh {

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;


	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
	unsigned int indexCount = 0;


	void createMesh(float radius = 1.0f, unsigned int sectorCount = 36, unsigned int stackCount = 24);

	std::vector<float> flatten() const;

	void uploadToGPU();

	void draw() const;

	void destroySphereMesh();

	void drawSphereMesh();

};