#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Mesh
{
public:
	virtual void render() const = 0;
};



struct SphereMesh : public Mesh {

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
	void render() const override;
	void destroySphereMesh();

};

struct CubeMesh : public Mesh
{
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
	unsigned int indexCount = 0;

	std::vector<float> vertices = {
		// 3p 3n 2uv
		// front face
		-1, -1,  1,   0, 0, 1,   0, 0,
		 1, -1,  1,   0, 0, 1,   1, 0,
		 1,  1,  1,   0, 0, 1,   1, 1,
		-1,  1,  1,   0, 0, 1,   0, 1,

		// back face
		-1, -1, -1,   0, 0, -1,  0, 0,
		 1, -1, -1,   0, 0, -1,  1, 0,
		 1,  1, -1,   0, 0, -1,  1, 1,
		-1,  1, -1,   0, 0, -1,  0, 1,
	};

	std::vector<unsigned int> indices = {
		// front
		0, 1, 2, 2, 3, 0,
		// right
		1, 5, 6, 6, 2, 1,
		// back
		5, 4, 7, 7, 6, 5,
		// left
		4, 0, 3, 3, 7, 4,
		// top
		3, 2, 6, 6, 7, 3,
		// bottom
		4, 5, 1, 1, 0, 4
	};



	void createCubeMesh();
	void uploadToGPU();
	void render() const override;
	void renderWireFrame();
};