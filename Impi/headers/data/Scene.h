#pragma once
#include <vector>
#include <rendering/assets/RenderableParticle.h>

class Scene {
public:
	std::vector<RenderableParticle> particles;

	void update(float dt);
	void draw(unsigned int shaderProgram) const;
};