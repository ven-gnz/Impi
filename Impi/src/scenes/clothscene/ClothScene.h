#pragma once

#include <src/physics/Cloth.h>
#include <src/scenes/Scene.h>

class ClothScene : public Scene
{

	VerletCloth cloth;
	Vector3 color1;
	Vector3 color2;

	real clothWidth;
	real clothHeight;

public:

	ClothScene(Camera& camera, real clothWidth, real clothHeight);

	void setClothColors(Vector3 color1, Vector3 color2);

	void update(real dt) override;

	void draw(Renderer& renderer, Camera& camera) override;


};