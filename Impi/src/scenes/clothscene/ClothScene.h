#pragma once

#include <src/physics/Cloth.h>
#include <src/scenes/Scene.h>


struct RenderableClothVertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 col;
};

class ClothScene : public Scene
{

	VerletCloth cloth;
	Vector3 color1;
	Vector3 color2;

	real clothWidth;
	real clothHeight;

	std::vector<RenderableClothVertex> renderableVertices;
	GLuint clothVAO = 0;
	GLuint clothVBO = 0;
	GLuint clothEBO = 0;

public:

	std::vector<GLuint> indices;
	std::vector<GLuint> calculate_indices(const VerletCloth& verletCloth);

	ClothScene(Camera& camera, real clothWidth, real clothHeight);

	//void setClothColors(Vector3 color1, Vector3 color2);

	void init_datastream();

	void fill_renderbuffer();

	void upstream_renderbuffer();

	void update(real dt) override;

	void draw(Renderer& renderer, Camera& camera) override;

	Vector3 windForce;

	void onActivate() override;


};