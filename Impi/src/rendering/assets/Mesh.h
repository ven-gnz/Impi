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